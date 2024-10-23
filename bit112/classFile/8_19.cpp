#include <iostream>
using namespace std;
#include <vector>
#include <stack>
template <class InputIterator,class Compare>
void QuickSort(InputIterator lhs,InputIterator rhs,Compare _cmp =  std::less())
{
    stack<InputIterator> sk;
    sk.push(rhs);
    sk.push(lhs);
    while(!sk.empty())
    {
        InputIterator begin = sk.top();
        sk.pop();
        InputIterator end = sk.top();
        sk.pop();
       



     InputIterator keyi = begin;          
     InputIterator prev = begin;
     InputIterator cur = begin + 1;





        if(end - begin > 1)
        {
        
        
        
            while(cur < end)
            {
                if(_cmp(*cur,*keyi) && cur != ++prev ){ std::swap(*cur,*(prev)); }
                cur++;
            std::swap(*keyi,*prev);
            sk.push(end);
            sk.push(prev + 1);
            sk.push(prev);
            sk.push(begin);
            }
        }
    };
}
void test()
{
    vector<int> arr = {2,23,43,123,32,4,2,1,31,1};
    QuickSort(arr.begin(),arr.end(),[](int left,int right){return left < right;});
    for(auto e : arr) { cout << e << " "; };
    cout << endl;
}
int main()
{
    test();
    return 0;
}
