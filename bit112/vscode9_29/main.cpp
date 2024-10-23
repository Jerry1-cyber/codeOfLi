#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <functional>
using std::function;using task_t = std::function<int(const char*, char* const[])>;
using std::cin;
#include <unordered_map>
#include <map>
using std::cout; 
using std::string;
#include <vector>
using namespace std;
//这里我们实现一个离散型随机变量的的代码
//这里我们设计一个可以针对离散型随机变量的统一的接口
void Prob()
{
    unordered_map<string,vector<string>> utask;
    utask["几何分布"] = {"/bin/python3","python3","./GeoDistribution.py"};
    utask["超几何分布"] = {"/bin/python3","python3","./BeyondGeoDistribution.py"};
    utask["二项分布"] = {"/bin/python3","python3","./BinaryDistribution.py"};
    while(true){
        string choice;
        cout << "这道题目的离散的类型:";
        cin >> choice;
        //创建子进程
        pid_t pid = fork();
        if(pid == 0){
            vector<string>& tuple = utask[choice];
            execl(tuple[0].c_str(),tuple[1].c_str(),tuple[2].c_str(),nullptr);
            exit(1);//子进程异常退出
        }
        int status = 0;
        pid_t rid = waitpid(pid,&status,0);//阻塞式等待
        if(rid){
            cout << "等待成功,进程处于正常运行的状态" << endl;
        }else{
             cout << "进程异常" << endl;
             if(WIFCONTINUED(status)){
                cout << "正常退出" << endl;
             }else cout << "异常退出信息" << WEXITSTATUS(status) << endl;
        }
        cout << "你要继续吗(yes/no):" << endl;
        cin >> choice;
        if(choice == "no" || choice == "No" || choice == "NO") break;
        pid = fork();
        if(pid == 0){
            execl("/bin/clear",nullptr);
            exit(1);
        }
        rid = waitpid(pid,nullptr,0);

    }
    cout << "正常退出" << endl;

}
int main()
{
    Prob();
    return 0;
}