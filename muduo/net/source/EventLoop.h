#ifndef MUDUO_NET_EVENTLOOP_H
#define MUDUO_NET_EVENTLOOP_H

#include <muduo/base/CurrentThread.h>
#include <muduo/base/Thread.h>
#include <muduo/base/noncopyable.h>
#include <muduo/base/Timestamp.h>
//#include <muduo/net/Channel.h>

#include <vector>
#include <memory>

namespace muduo
{
namespace net
{

class Channel;
class Poller;

class EventLoop : noncopyable
{
public:
  EventLoop();
  ~EventLoop();

  void loop();
  //结束loop循环
  void quit();
  //poll结束时间戳，基本等于数据到达时间
  Timestamp pollReturnTime() const { return pollReturnTime_; }

  void updateChannel(Channel *channel);
  void removeChannel(Channel *channel);

  void assertInLoopThread()
  {
      if (!isInLoopThread())
      {
          abortNotInLoopThread();
      }
  }
  bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }
  static EventLoop *getEventLoopOfCurrentThread();

private:
  void abortNotInLoopThread();

  void printActiveChannels() const;

  typedef std::vector<Channel *> ChannelList;

  bool looping_;
  bool quit_;
  bool eventHandling_;

  const pid_t threadId_;
  Timestamp pollReturnTime_;
  std::unique_ptr<Poller> poller_;
  ChannelList activeChannels_;
  Channel *currentActiveChannel_;
};

} // namespace net
} // namespace muduo

#endif