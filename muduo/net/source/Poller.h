#ifndef MUDUO_NET_POLLER_H
#define MUDUO_NET_POLLER_H

#include <muduo/base/noncopyable.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/EventLoop.h>

#include <vector>

namespace muduo
{
namespace net
{

class Channel;

class Poller : muduo::noncopyable
{
public:
  typedef std::vector<Channel *> ChannelList;

  Poller(EventLoop *loop);
  virtual ~Poller();

  virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;
  //update I/O事件
  virtual void updateChannel(Channel *channel) = 0;
  //将I/O事件从channel中移除
  virtual void removeChannel(Channel *channel) = 0;

  static Poller *newDefaultPoller(EventLoop *loop);

  void assertInLoopThread()
  {
      ownerLoop_->assertInLoopThread();
  }

private:
  EventLoop *ownerLoop_;
};

} // namespace net
} // namespace muduo

#endif