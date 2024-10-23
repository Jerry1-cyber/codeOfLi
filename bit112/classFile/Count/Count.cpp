#include "Count.h"
void Process::menu()
{
    std::cout << "Progress begin" << endl;
    ProgressBar();
    std::cout << "Progress end" << endl;
}
void Process::ProgressBar()
{
    int pos = 0;
    const char* ch = "|\\-/";
    while(pos < NUM)
    {
        _str[pos] = '#';
        cout << '[' << _str << ']'<< '[' << pos + 1 << ']' << '[' << ch[pos % 4] << ']' << '\r';
        fflush(stdout);
        usleep(100000);
        pos++;
    }
    cout << endl;
}
