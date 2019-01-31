#include <muduo/base/ThreadLocalSingleton.h>
#include <muduo/base/CurrentThread.h>
#include <muduo/base/Thread.h>
#include <muduo/base/noncopyable.h>
#include <boost/bind.hpp>
#include <cstdio>

class Test : muduo::noncopyable
{
public:
  Test()
  {
      printf("tid=%d, constructing %p\n", muduo::CurrentThread::tid(), this);
  }
  ~Test()
  {
      printf("tid=%d, destructing %p %s\n", muduo::CurrentThread::tid(), this, name_.c_str());
  }

  const std::string &name() const { return name_; }
  void setName(const std::string &n) { name_ = n; }

private:
  std::string name_;
};

void threadFunc(const char* changeTo)
{
  printf("in threadFunc tid=%d, %p name=%s\n",
         muduo::CurrentThread::tid(),
         &muduo::ThreadLocalSingleton<Test>::instance(),
         muduo::ThreadLocalSingleton<Test>::instance().name().c_str());
  muduo::ThreadLocalSingleton<Test>::instance().setName(changeTo);
  printf("changed in threadFunc tid=%d, %p name=%s\n",
         muduo::CurrentThread::tid(),
         &muduo::ThreadLocalSingleton<Test>::instance(),
         muduo::ThreadLocalSingleton<Test>::instance().name().c_str());
}

int main()
{
    muduo::ThreadLocalSingleton<Test>::instance().setName("main");
    muduo::Thread t1(boost::bind(threadFunc, "thread1"));
    muduo::Thread t2(boost::bind(threadFunc, "thread2"));
    t1.start();
    t2.start();
    t1.join();
    printf("in main thread tid=%d, %p name=%s\n",
           muduo::CurrentThread::tid(),
           &muduo::ThreadLocalSingleton<Test>::instance(),
           muduo::ThreadLocalSingleton<Test>::instance().name().c_str());
    t2.join();

    pthread_exit(0);
}