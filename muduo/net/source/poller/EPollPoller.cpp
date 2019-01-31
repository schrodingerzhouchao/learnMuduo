#include "EpollPoller.h"
#include <muduo/base/Logging.h>
#include <muduo/net/Channel.h>
#include <muduo/net/Poller.h>

#include <cassert>
#include <cerrno>
#include <poll.h>
#include <sys/epoll.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

static_assert(EPOLLIN == POLLIN, "epoll uses same flag values as poll");
static_assert(EPOLLPRI == POLLPRI, "epoll uses same flag values as poll");
static_assert(EPOLLOUT == POLLOUT, "epoll uses same flag values as poll");
static_assert(EPOLLRDHUP == POLLRDHUP, "epoll uses same flag values as poll");
static_assert(EPOLLERR == POLLERR, "epoll uses same flag values as poll");
static_assert(EPOLLHUP == POLLHUP, "epoll uses same flag values as poll");

namespace
{
const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;
}

EPollPoller::EPollPoller(EventLoop *loop)
    : Poller(loop),
      epollfd_(::epoll_create1(EPOLL_CLOEXEC)),
      events_(kInitEventListSize)
{
    if (epollfd_ < 0)
        LOG_SYSFATAL << "EPollPoller::EPollPoller";
}

EPollPoller::~EPollPoller()
{
    ::close(epollfd_);
}

//epoll_wait()
//return Timestamp ?
Timestamp EPollPoller::poll(int timeoutMs,ChannelList *activeChannels)
{
    LOG_TRACE << "fd total count " << channels_.size();
    int numEvents = ::epoll_wait(epollfd_, events_.data(), static_cast<int>(events_.size()), timeoutMs);

    int savedErrno = errno;
    Timestamp now(Timestamp::now());
    if (numEvents > 0)
    {
        LOG_TRACE << numEvents << " events happened";
        fillActiveChannels(numEvents, activeChannels);
        if (implicit_cast<size_t>(numEvents) == events_.size())
            events_.resize(events_.size() * 2);
    }
    else if (numEvents == 0)
        LOG_TRACE << " nothing happened";
    else
        LOG_SYSERR << "EPOLlPoller::poll()";
    return now;
}

// 历遍，找到有活动事件的fd，把它对应的Channel填入到activeChannel
void EPollPoller::fillActiveChannels(int numEvents, ChannelList *activeChannels) const
{
    assert(implicit_cast<size_t>(numEvents) <= events_.size());
    for (int i = 0; i < numEvents; ++i)
    {
        Channel *channel = static_cast<Channel *>(events_[i].data.ptr);
    #ifndef NDEBUG
        int fd = channel->fd();
        ChannelMap::const_iterator it = channels_.find(fd);
        assert(it != channels_.end());
        assert(it->second == channel);
    #endif
        channel->set_revents(events_[i].events);
        activeChannels->push_back(channel);
    }
}

//
void EPollPoller::updateChannel(Channel *channel)
{
    Poller::assertInLoopThread();
    LOG_TRACE << "fd = " << channel->fd() << " events = " << channel->events();
    const int index = channel->index();
    if (index == kNew || index == kDeleted)
    {
        int fd = channel->fd();
        if (index == kNew)
        {
            assert(channels_.find(fd) == channels_.end());
            channels_[fd] = channel;
        }
        else
        {
            assert(channels_.find(fd) != channels_.end());
            assert(channels_[fd] == channel);
        }
        channel->set_index(kAdded);
        update(EPOLL_CTL_ADD, channel);
    }
    else
    {
        int fd = channel->fd();
        (void)fd;
        assert(channels_.find(fd) != channels_.end());
        assert(channels_[fd] == channel);
        assert(index == kAdded);
        if (channel->isNoneEvent())
        {
            update(EPOLL_CTL_DEL, channel);
            channel->set_index(kDeleted);
        }
        else
        {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

void EPollPoller::removeChannel(Channel *channel)
{
    Poller::assertInLoopThread();
    int fd = channel->fd();
    LOG_TRACE << "fd = " << fd;
    assert(channels_.find(fd) != channels_.end());
    assert(channels_[fd] == channel);
    assert(channel->isNoneEvent());
    int index = channel->index();
    assert(index == kAdded || index == kDeleted);
    size_t n = channels_.erase(fd);
    (void)n;
    assert(n == 1);
    if (index == kAdded)
        update(EPOLL_CTL_DEL, channel);
    channel->set_index(kNew);
}

void EPollPoller::update(int operation, Channel *channel)
{
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = channel->events();
    event.data.ptr = channel;
    int fd = channel->fd();
    if (::epoll_ctl(epollfd_, operation, fd, &event) < 0)
    {
        if (operation == EPOLL_CTL_DEL)
        {
            LOG_SYSERR << "epoll_ctl op = " << operation << " fd = " << fd;
        }
        else
        {
            LOG_SYSFATAL << "epoll_ctl op = " << operation << " fd = " << fd;
        }
    }
}