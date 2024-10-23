#include <iostream>
using namespace std;
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>
vector<int> data;
void Save()
{
    pid_t id = forkq();
    if(id == 0)
        exit(0)
    pid_t rid = waitpid(id,)
}
int main()
{
    int cnt = 1;
    while(true){
        data.push_back(cnt++);
        sleep(1);
        if(cnt % 10 == 0){
            Save();
        }
    }

}
