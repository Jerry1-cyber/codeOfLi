#include <iostream>
using std::cin;
using std::cout;
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <fstream>
using std::ofstream;
using std::vector;
#include <string>
using std::string;
vector<int> arr;
const string backup(".backup");
int BackUp(){
    ofstream ofs(backup);
    for(auto e : arr)
        ofs << e << " ";
    ofs.close();
    return 0;
}
int main()
{
    int count = 0;
    while(true){
        count++;
        arr.push_back(count);
        if(count % 10 == 0){
            pid_t pid = fork();//这里直接进行备份
            if(pid == 0){
                BackUp();//儿子进程
                exit(0);
            }
            pid_t rid = waitpid(pid,nullptr,0);//阻塞式等待
            if(rid == 0) printf("未等到\n");
            else printf("已经等到\n");

        }
        sleep(1);
    }
}
