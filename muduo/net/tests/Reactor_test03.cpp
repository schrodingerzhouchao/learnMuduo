#include <muduo/net/Channel.h>
#include <muduo/net/EventLoop.h>
#include <functional>
#include <cstdio>
#include <sys/timerfd.h>

using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;

EventLoop *g_loop;
int timerfd;
const int LOOP_NUM = 10;

void timeout(Timestamp receiveTime)
{
    printf("Timeout!\n");
    uint64_t howmany;
    ::read(timerfd, &howmany, sizeof howmany);
    g_loop->quit();
}

int main()
{
    EventLoop loop;
    g_loop = &loop;

    timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    Channel channel(&loop, timerfd);
    channel.setReadCallback(std::bind(timeout,_1));
    channel.enableReading();

    struct itimerspec howlong;
    bzero(&howlong, sizeof howlong);
    howlong.it_value.tv_sec = 5;
    ::timerfd_settime(timerfd, 0, &howlong, nullptr);

    loop.loop();

    ::close(timerfd);
}