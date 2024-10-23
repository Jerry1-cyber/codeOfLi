#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
extern char **environ;
int main(int argc,char *argv[])

{
    printf("%d\n",argc);
    for(int i = 0;i < argc;i++)
        printf("%s\n",argv[i]);
    if(strcmp(argv[0],"-choice1")) 
        printf("you choose choice1\n");
    else if(strcmp(argv[1],"choice2"))
        printf("you choose choice2\n");
    return 0;
}
