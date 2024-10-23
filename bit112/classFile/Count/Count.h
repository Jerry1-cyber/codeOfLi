#include <iostream>
#include <unistd.h>
using std::string;
using std::cout;
using std::endl;
enum { NUM = 100, };
class Process{
public:
    Process():_str(NUM,' '){};
    void menu();
    void ProgressBar();
private:
    string _str;
};
