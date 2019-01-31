#include <muduo/net/Poller.h>
//#include <muduo/net/poller/EPollPoller.h>
#include "EpollPoller.h"
#include <cstdlib>

using namespace muduo::net;

Poller *Poller::newDefaultPoller(EventLoop *loop)
{
    return new EPollPoller(loop);
}