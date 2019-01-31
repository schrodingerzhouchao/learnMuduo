// TimeZone valid()
// static_cast<bool>(data_) (data_ : smartptr)
#include <iostream>
using namespace std;

int main()
{
    int a=10;
    int b=0;
    int *pa=&a;
    int *pb=&b;
    int *pnull=nullptr;
    
    cout<<boolalpha;
    cout<<"(bool)(p->10)"<<(bool)(pa)
        <<endl
        <<"static_cast<bool>(p->10)"<<static_cast<bool>(pa)
        <<endl;
    
    cout<<"(bool)(p->0)"<<(bool)(pb)
        <<endl
        <<"static_cast<bool>(p->0)"<<static_cast<bool>(pb)
        <<endl;
    
    cout<<"(bool)(p->nullptr)"<<(bool)(pnull)
        <<endl
        <<"static_cast<bool>(p->nullptr)"<<static_cast<bool>(pnull)
        <<endl;

    char *c;
    char *d=nullptr;
    cout<<"(bool)(c)"<<(bool)(c)<<endl;
    cout<<"static_cast<bool>(d)"<<static_cast<bool>(d)<<endl;

    return 0;
}
