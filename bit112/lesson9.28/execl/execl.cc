#include <iostream>
using namespace std;
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    getenv("PATH");
    pid_t pid = fork();
    if(pid == 0){
        sleep(3);
        //儿子进程
        execl("/bin/cowsay","cowsay","hollo bit",nullptr);
        exit(1);//如果失败了就调用这里
    }
    //父亲阻塞等待
    pid_t rid = waitpid(pid,nullptr,0);
    cout << "等待成功" << endl;
    return 0;
}
