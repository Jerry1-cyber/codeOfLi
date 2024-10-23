#include <stdio.h>
int main()
{
    FILE* pf = fopen("log.txt","w");
    const char* str = "hello world";
    fputs(str,pf);
    return 0;
}
