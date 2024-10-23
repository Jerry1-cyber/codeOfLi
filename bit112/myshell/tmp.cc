#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

const int basesize = 1024;
const int argvnum = 64;
const int envnum = 64;
 
// 全局的命令行参数表
char *gargv[argvnum];
int gargc = 0;

// 我的系统的环境变量
char *genv[envnum];

// 全局的当前shell工作路径 
char pwd[basesize];
char pwdenv[basesize];

string GetUserName()
{
    string name = getenv("USER");
    return name.empty() ? "None" : name;
}

string GetHostName()
{
    string hostname = getenv("HOSTNAME");
    return hostname.empty() ? "None" : hostname;
}

string GetPwd()
{
    if(nullptr == getcwd(pwd, sizeof(pwd))) return "None";
    snprintf(pwdenv, sizeof(pwdenv),"PWD=%s", pwd);
    putenv(pwdenv); // PWD=XXX
    return pwd;

    //string pwd = getenv("PWD");
    //return pwd.empty() ? "None" : pwd;
}

string MakeCommandLine()
{
    // [whb@bite-alicloud myshell]$ 
    char command_line[basesize];
    snprintf(command_line, basesize, "[%s@%s %s]# ",\
            GetUserName().c_str(), GetHostName().c_str(), GetPwd().c_str());
    return command_line;
}

void PrintCommandLine() // 1. 命令行提示符
{
    printf("%s", MakeCommandLine().c_str());
    fflush(stdout);//这里需要我们刷新缓冲区
}

bool GetCommandLine(char command_buffer[], int size)   // 2. 获取用户命令
{
    // 我们认为：我们要将用户输入的命令行，当做一个完整的字符串
    // "ls -a -l -n"
    char *result = fgets(command_buffer, size, stdin);
    if(!result)
    {
        return false;
    }
    command_buffer[strlen(command_buffer)-1] = 0;
    if(strlen(command_buffer) == 0) return false;
    return true;
}

void ParseCommandLine(char command_buffer[], int len) // 3. 分析命令
{
    (void)len;
    memset(gargv, 0, sizeof(gargv));
    gargc = 0;
    // "ls -a -l -n"
    const char *sep = " ";
    gargv[gargc++] = strtok(command_buffer, sep);
    // =是刻意写的
    while((bool)(gargv[gargc++] = strtok(nullptr, sep)));
    gargc--;
}

void debug()
{
    printf("argc: %d\n", gargc);
    for(int i = 0; gargv[i]; i++)
    {
        printf("argv[%d]: %s\n", i, gargv[i]);
    }
}
// 在shell中
// 有些命令，必须由子进程来执行
// 有些命令，不能由子进程执行，要由shell自己执行 --- 内建命令 built command
bool ExecuteCommand()   // 4. 执行命令
{
    // 让子进程进行执行
    pid_t id = fork();
    if(id < 0) return false;
    if(id == 0)
    {
        //子进程
        // 1. 执行命令'/
        execvp(gargv[0], gargv);
        // 2. 退出
        exit(1);
    }
    int status = 0;
    pid_t rid = waitpid(id, &status, 0);
    if(rid > 0)
    {
       // Do Nothing
       return true;
    }
    return false;
}

void AddEnv(const char *item)
{
    int index = 0;
    while(genv[index])
    {
        index++;
    }

    genv[index] = (char*)malloc(strlen(item)+1);
    strncpy(genv[index], item, strlen(item)+1);
    genv[++index] = nullptr;
}
// shell自己执行命令，本质是shell调用自己的函数
bool CheckAndExecBuiltCommand()
{
    if(strcmp(gargv[0], "cd") == 0)
    {
        // 内建命令
        if(gargc == 2)
        {
            chdir(gargv[1]);
        }
        return true;
    }
    else if(strcmp(gargv[0], "export") == 0)
    {
        // export也是内建命令
        if(gargc == 2)
        {
            AddEnv(gargv[1]);
        }
        return true;
    }
    else if(strcmp(gargv[0], "env") == 0)
    {
        for(int i = 0; genv[i]; i++)
        {
            printf("%s\n", genv[i]);
        }
        return true;
    }
    return false;
}

// 作为一个shell，获取环境变量应该从系统的配置来
// 我们今天就直接从父shell中获取环境变量
void InitEnv()
{
    extern char **environ;
    int index = 0;
    while(environ[index])
    {
        genv[index] = (char*)malloc(strlen(environ[index])+1);
        strncpy(genv[index], environ[index], strlen(environ[index])+1);
        index++;
    }
    genv[index] = nullptr;
}

int main()
{
    InitEnv();//对环境变量进行初始化
    char command_buffer[basesize];
    while(true)
    {
        PrintCommandLine(); // 1. 命令行提示符
        // command_buffer -> output
        if( !GetCommandLine(command_buffer, basesize) )   // 2. 获取用户命令
        {
            continue;
        }
        //printf("%s\n", command_buffer);
        //ls
        //"ls -a -b -c -d"->"ls" "-a" "-b" "-c" "-d"
        ParseCommandLine(command_buffer, strlen(command_buffer)); // 3. 分析命令

        if ( CheckAndExecBuiltCommand() )
        {
            continue;
        }

        ExecuteCommand();   // 4. 执行命令
    }
    return 0;
}