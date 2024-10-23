#include <iostream>
using namespace std;
#include <unistd.h>
#include <sys/types.h>
int main(){
    while(true)
        cout << "hello world:" << getpid() << " " << getppid() << endl;
    return 0;
}
