#include <muduo/net/EventLoop.h>
#include <muduo/base/Thread.h>


muduo::net::EventLoop *g_loop;

void threadFunc()
{
    g_loop->loop();
}

int main()
{
    muduo::net::EventLoop loop;     // main thread, loop() should run in this thread
    g_loop = &loop;
    muduo::Thread t(threadFunc);    // new thread
    t.start();
    t.join();

    return 0;
}