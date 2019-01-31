#include <muduo/net/EventLoop.h>
#include <muduo/base/Logging.h>
#include <muduo/net/Poller.h>


using namespace muduo;
using namespace muduo::net;

namespace   //only visible in this file
{
__thread EventLoop *t_loopInThisThread = 0;

const int kPollTimeMs = 10000;
}

EventLoop *EventLoop::getEventLoopOfCurrentThread()
{
    return t_loopInThisThread;
}

EventLoop::EventLoop()
    : looping_(false),
      quit_(false),
      eventHandling_(false),
      threadId_(CurrentThread::tid()),
      poller_(Poller::newDefaultPoller(this)),
      currentActiveChannel_(nullptr)
{
    LOG_TRACE << "EventLoop created " << this << " in thread " << threadId_;
    if (t_loopInThisThread)
    {
        LOG_FATAL << "Another EventLoop " << t_loopInThisThread << " exists in this thread " << threadId_;
    }
    else
    {
        t_loopInThisThread = this;
    }
}

EventLoop::~EventLoop()
{
    t_loopInThisThread = nullptr;
}

void EventLoop::loop()
{
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;
    LOG_TRACE << "EventLoop " << this << " start looping";
    //::poll(nullptr, 0, 5 * 1000);
    while (!quit_)
    {
        activeChannels_.clear();
        pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);

        if (Logger::logLevel() <= Logger::TRACE)
            printActiveChannels();

        eventHandling_ = true;
        for (ChannelList::iterator it = activeChannels_.begin(); it != activeChannels_.end(); ++it)
        {
            currentActiveChannel_ = *it;
            currentActiveChannel_->handleEvent(pollReturnTime_);
        }
        currentActiveChannel_ = nullptr;
        eventHandling_ = false;
    }

    LOG_TRACE << "EventLoop " << this << " stop looping";
    looping_ = false;
}

void EventLoop::quit()
{
    quit_ = true;
    if (!isInLoopThread())
    {
        ;
    }
}

void EventLoop::updateChannel(Channel *channel)
{
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    poller_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel *channel)
{
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    if (eventHandling_)
    {
        assert(currentActiveChannel_ == channel ||
               std::find(activeChannels_.begin(), activeChannels_.end(), channel) == activeChannels_.end());
    }
    poller_->removeChannel(channel);
}

void EventLoop::abortNotInLoopThread()
{
    LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
              << " was created in threadId_ = " << threadId_
              << ", current thread id = " << CurrentThread::tid();
}

void EventLoop::printActiveChannels() const
{
    for (ChannelList::const_iterator it = activeChannels_.begin();
         it != activeChannels_.end(); ++it)
    {
        const Channel *ch = *it;
        LOG_TRACE << "{" << ch->reventsToString() << "}";
    }
}