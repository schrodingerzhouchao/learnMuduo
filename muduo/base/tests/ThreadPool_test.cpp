#include <muduo/base/ThreadPool.h>
#include <muduo/base/CountDownLatch.h>
#include <muduo/base/CurrentThread.h>

#include <boost/bind.hpp>
#include <cstdio>

void print()
{
    printf("tid=%d\n", muduo::CurrentThread::tid());
}

void printString(const std::string& str)
{
    printf("tid=%d, str=%s\n", muduo::CurrentThread::tid(), str.c_str());
}

int main()
{
    muduo::ThreadPool pool("MainThreadPool");
    pool.start(5);

    pool.run(print);
    for (int i = 0; i < 100; ++i)
    {
        char buf[32];
        snprintf(buf, sizeof(buf), "task %d", i);
        pool.run(boost::bind(printString, std::string(buf)));
    }
    muduo::CountDownLatch latch(3);
    for (int i = 0; i < 3; ++i)
    {
        pool.run(boost::bind(&muduo::CountDownLatch::countDown, &latch));
        
    }
    latch.wait();
    pool.stop();
}