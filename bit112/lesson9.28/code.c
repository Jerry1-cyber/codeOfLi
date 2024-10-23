#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <error.h>
#include <string.h>
int count = 0;
int main()
{
    printf("%s\n",strerror(1));
    pid_t id = fork();
    if(!id){
        //孩子进程
        while(1){
            printf("pid:%d ppid:%d\n",getpid(),getppid());
            printf("I am a kid:count:%d\n",count++);
            sleep(2);
            printf("%p\n",&count);
        }
    }
    if(id){
        //父亲进程
        while(1){
            printf("pid:%d ppid:%d\n",getpid(),getppid());
            printf("my kid uid:%d,count:%d\n",id,count);
            printf("%p\n",&count);
            sleep(2);
        }
    }
    return 0;
}
