#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;
int main()
{
    pid_t pid = getpid();
    pid_t ppid = getppid();
    while(true){
        cout << "pid: "<< pid << " ppid: "<< ppid << endl;
    }
    return 0;
}
