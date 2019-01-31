#include <muduo/base/CurrentThread.h>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;
using namespace muduo;
using namespace muduo::CurrentThread;

static string s;

void print()
{
    cout<<"Hello,World!"<<endl;
    s = stackTrace(true);
}

int main()
{
    print();
    //string s=stackTrace(true);
    cout<<s<<endl;

    return 0;
}

