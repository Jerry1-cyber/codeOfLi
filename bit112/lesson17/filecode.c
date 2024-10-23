#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    printf("%d\n",getumask());
    int fd1 = open("log.txt",O_WRONLY | O_CREAT | O_APPEND,0666);
    const char* str = "hello bit\n";
    write(fd1,str,sizeof(str));
    printf("%d\n",fd1);

    return 0;
}
