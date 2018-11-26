#include <muduo/base/Exception.h>
#include <muduo/base/CurrentThread.h>
#include <cstdio>


class Bar
{
public:
  void test()
  {
      throw muduo::Exception("oops");
  }
};

void foo()
{
    Bar b;
    b.test();
}

int main()
{
    try
    {
        foo();
    }
    catch (const muduo::Exception& e)
    {
        printf("reason: %s\n", e.what());
        printf("stack trace:\n%s\n", e.stackTrace());

        return 0;
    }
}