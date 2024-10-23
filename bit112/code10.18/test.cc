#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
const int env_size = 64;
char* genv[env_size];
void getEnv()
{
    extern char** environ;
    for(int i = 0;environ[i];i++)
    {
        genv[i] = (char*)malloc(sizeof(environ[i]) + 1);
        strncpy(genv[i],environ[i],sizeof(genv[i]));
    }
    const char* argv[] = {
        "./chlid.exe",
        nullptr;
    };
    pid_t pid = fork();
    if(pid == 0){
        //这里表示进入子进程
        execv(argv[0],argv);
        exit(1);
    }
    pid_t rid = waitpid(pid,nullptr,0);
    if(rid) printf("等待成功\n");
    
}
int main()
{
    
    return 0;
}
