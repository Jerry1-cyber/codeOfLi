#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

//这里我还是采用c++的风格来进行编程
//我们这里函数的命名采用小驼峰的命名的规则
string command_line;
const int argvnum = 64;
const int basesize = 1024;
char* gargv[argvnum];
int gargc = 0;
char pwd[basesize];
char pwdenv[basesize];
string getUserName(){
    string username = getenv("USER");
    return username.empty() ? "None" : username;
}

string getPwd(){
    //string pwd = getenv("PWD");
    
    if(!getcwd(pwd,sizeof(pwd))) return "None";
    snprintf(pwdenv,basesize,"PWD=%s",pwd);
    putenv(pwdenv);
    return pwd;
}

string getHostName(){
    string hostname = getenv("HOSTNAME");
    return hostname.empty() ? "None" : hostname;
}

string getBaseData(){
    return "[" + getUserName() + "@" + getHostName() + " " + getPwd() + "]@ ";
}

void printBaseData(){
    std::cout << getBaseData();
}

bool getCommandLine(char* command_line,int max_size){
    if(!fgets(command_line,max_size,stdin)) return false;
    command_line[strlen(command_line) - 1] = 0;
    if(strlen(command_line) == 0) return false;
    return true;
}

void paraseCommandLine(char* command_line,int size){
    memset(gargv,0,sizeof(gargv));
    gargc = 0;
    const char* seq = " ";
    gargv[gargc++] = strtok(command_line,seq);
    while(gargv[gargc++] = strtok(nullptr,seq));
    gargc--;
}
// void debug(){
//     printf("argc:%d\n",gargc);
//     for(int i = 0;i < gargc;i++)
//         printf("argv[%d]:%s\n",i,gargv[i]);
// }
//有些命令,不能由子进程执行,要有shell自己本身来执行, --内建命令
bool executeCommandLine(){
    pid_t pid = fork();
    if(pid == -1) return false;//创建子进程失败
    else if(pid == 0){
        //子进程
        execvp(gargv[0],gargv);
        exit(1);//执行失败
    }
    int status = 0;
    pid_t rid = waitpid(pid,&status,0);
    if(rid > 0) {
        return true;
    }
    return false;
}
bool checkAndExecuteBuildLine(){
    if(strcmp(gargv[0],"cd") == 0){
        if(gargc == 2)
            chdir(gargv[1]);
        return true;
    }

    return false;
}
int main()
{
    while(true)
    {
        printBaseData();
        char command_line[basesize] = { 0 };
        if(getCommandLine(command_line,basesize)){
            paraseCommandLine(command_line,strlen(command_line));
            if(checkAndExecuteBuildLine()){
                continue;
            }
            executeCommandLine();
        }
    }
    return 0;
}