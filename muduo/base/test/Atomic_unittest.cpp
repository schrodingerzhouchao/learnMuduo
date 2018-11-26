
#include <muduo/base/Atomic.h>
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    cout << "hello" << endl;
    {
        muduo::AtomicInt64 a0;
        assert(a0.get() == 0);
        assert(a0.getAndAdd(1) == 0);
        assert(a0.get() == 1);
        assert(a0.addAndGet(2) == 3);
        assert(a0.get() == 3);
        assert(a0.incrementAndGet() == 4);
        assert(a0.get() == 4);
        assert(a0.addAndGet(-10) == -6);
    }
    {
        
        muduo::AtomicInt32 a1;
        int32_t b = a1.get();
        cout << b << endl;
        
        b = a1.getAndAdd(10);
        cout << a1.get() << endl;
        cout << b << endl;
        b = a1.addAndGet(11);
        cout << a1.get() << endl;
        cout << b << endl;
        cout << sizeof(a1) << " " << sizeof(b) << endl;
    }

    return 0;
}
