#include <muduo/base/Date.h>
#include <iostream>
#include <cassert>
#include <cstdio>

using namespace std;
using namespace muduo;

int runnian(int year)
{
    if(year%400==0)
        return 1;
    else if(year%100==0)
        return 0;
    else if(year%4==0)
        return 1;
    else
        return 0;
}

int main()
{
    time_t now=time(nullptr);
    struct tm t1=*gmtime(&now);
    struct tm t2=*localtime(&now);
    cout<<t1.tm_year+1900<<"-"<<t1.tm_mon+1<<"-"<<t1.tm_mday<<"~"<<t1.tm_hour<<":"<<t1.tm_min<<":"<<t1.tm_sec<<endl;
    cout<<t2.tm_year+1900<<"-"<<t2.tm_mon+1<<"-"<<t2.tm_mday<<"~"<<t2.tm_hour<<":"<<t2.tm_min<<":"<<t2.tm_sec<<endl;

    Date gmtoday(t1);
    printf("gmtoday:%s\n",gmtoday.toIsoString().c_str());
    printf("gmtoday-julian day number:%d\n",gmtoday.julianDayNumber());
    Date loctoday(t2);
    printf("loctoday:%s\n",loctoday.toIsoString().c_str());
    printf("loctoday-julian day number:%d\n",loctoday.julianDayNumber());


    int runnian_=0;
    for(int year=1987;year<2020;++year)
    {
        if(runnian(year)==1)
        {
            cout<<year<<" 润年"<<endl;

            ++runnian_;
        }
    }

    Date t3(2019,22,33);
    assert(static_cast<bool>(t3.toIsoString().c_str()));
    printf("t3:%s\n",t3.toIsoString().c_str());
    return 0;
}

