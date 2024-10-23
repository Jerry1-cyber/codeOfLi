#include <stdio.h>
int Sum(int x,int y){
    int sum = 0;
    int i = 0;
    for(i = 0;i < 10;i++)
        sum += (y - x);
    return sum;
}
int main()
{
    printf("process is running\n");
    int begin = 0, end = 10; 
    printf("the ending is:%d\n",Sum(begin,end));
    return 0;
}
