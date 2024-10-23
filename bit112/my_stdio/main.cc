#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
    printf("hello printf\n");
    fprintf(stdout,"printf fprintf\n");
    fflush(stdout);
    const char* str = "hello write\n";
    write(1,str,strlen(str));
    fork();
    return 0;
}
