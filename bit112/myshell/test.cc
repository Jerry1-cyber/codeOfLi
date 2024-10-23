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
int main()
{
    const string str = "AAA=111";
    putenv(str.c_str());
    pid_t pid = fork();
    if(pid == 0){
        extern char** environ;
        for(int i = 0; environ[i];i++)
            printf("argv[%d]:%s\n",i,environ[i]);
        exit(0);
    }

    pid_t rid = waitpid(pid,nullptr,0);
    return 0;
}
