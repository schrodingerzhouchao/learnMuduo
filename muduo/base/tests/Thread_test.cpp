#include <muduo/base/Thread.h>
#include <muduo/base/CurrentThread.h>
#include <muduo/base/Types.h>
#include <boost/bind.hpp>
#include <cstdio>
#include <ctime>

void threadFunc()
{
    printf("tid=%d\n", muduo::CurrentThread::tid());
}
void threadFunc2(int x)
{
    printf("tid=%d, x=%d\n", muduo::CurrentThread::tid(),x);
}

class Foo
{
public:
  explicit Foo(double x) : x_(x)
  {
  }

  void memberFunc()
  {
      printf("tid=%d, Foo::x_=%f\n", muduo::CurrentThread::tid(), x_);
  }
  void memberFunc2(const std::string &text)
  {
      printf("tid=%d, Foo::x_=%f, text=%s\n", muduo::CurrentThread::tid(), x_, text.c_str());
  }

private:
  double x_;
};


int main()
{
    printf("pid=%d, tid=%d\n", ::getpid(), muduo::CurrentThread::tid());

    muduo::Thread t1(threadFunc);
    t1.start();
    t1.join();

    muduo::Thread t2(boost::bind(threadFunc2, 33), "thread for free function with argument");
    t2.start();
    t2.join();

    Foo foo(87.33);
    muduo::Thread t3(boost::bind(&Foo::memberFunc, &foo), "thread for member function without argument");
    t3.start();
    t3.join();

    muduo::Thread t4(boost::bind(&Foo::memberFunc2, boost::ref(foo), std::string("chen shuo")));
    t4.start();
    t4.join();

    printf("number of created threads %d\n", muduo::Thread::numCreated());

    muduo::string st = muduo::CurrentThread::stackTrace(false);
    if (fork() == 0)
    {
        threadFunc();
    }
    timespec ts = {2, 0};
    nanosleep(&ts, nullptr);
    printf("stack trace:\n%s\n", st.c_str());

    return 0;
}