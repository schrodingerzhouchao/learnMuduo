#ifndef MUDUO_NET_CHANNEL_H
#define MUDUO_NET_CHANNEL_H

#include <memory>
#include <functional>
//#include <boost/function.hpp>
#include <muduo/base/noncopyable.h>
//#include <boost/shared_ptr.hpp>
//#include <boost/weak_ptr.hpp>
#include <muduo/base/Timestamp.h>


namespace muduo
{
namespace net
{

//前置声明。

//当需要知道类型的大小或者需要知道它的函数签名时，需要定义，也就是#include ""
//当需要类型的指针或者引用，前置声明就可以了
class EventLoop;

//事件分发。每个channel只属于一个eventloop，
//负责注册读写事件，并保存fd读写事件发生时调用的回调函数，如果POLL有读写事件发生则将这些时间添加到对应的channel中
//当有fd返回读写事件时，调用提前注册的回调函数处理读写事件

class Channel:muduo::noncopyable
{
public:
  typedef std::function<void()> EventCallback;                  //事件回调处理
  typedef std::function<void(Timestamp)> ReadEventCallback;     //读事件的回调处理

  Channel(EventLoop *loop, int fd);                             //每个channel只属于一个EventLoop
  ~Channel();

  void handleEvent(Timestamp receiveTime);
  //设置回调函数
  void setReadCallback(ReadEventCallback cb) { readCallBack_ = std::move(cb); }
  void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }
  void setCloseCallback(EventCallback cb) { closeCallback_ = std::move(cb); }
  void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }

  //?
  void tie(const std::shared_ptr<void> &);

  int fd() const { return fd_; }
  int events() const { return events_; }
  void set_revents(int revt) { revents_ = revt; }
  bool isNoneEvent() const { return events_ == kNoneEvent; }

  void enableReading() { events_ |= kReadEvent; update(); }
  void disableReading() { events_ &= ~kReadEvent; update(); }
  void enableWriting() { events_ |= kWriteEvent; update(); }
  void disableWriting() { events_ &= ~kWriteEvent; update(); }
  void diableAll() { events_ = kNoneEvent; update(); }

  bool isReading() const { return events_ & kReadEvent; }
  bool isWriting() const { return events_ & kWriteEvent; }

  //pollfd的index
  int index() { return index_; }
  void set_index(int idx) { index_ = idx; }

  //for debug
  string eventsToString() const;
  string reventsToString() const;

  void doNotLOgHUp() { logHup_ = false; }

  EventLoop *ownerLoop() { return loop_; }
  void remove();

private:
  static string eventsToString(int fd, int ev);

  void update();
  void handleEventWithGuard(Timestamp receiveTime);

  static const int kNoneEvent;
  static const int kReadEvent;
  static const int kWriteEvent;

  EventLoop *loop_;
  const int fd_;
  int events_;
  int revents_;
  int index_;
  bool logHup_;                     //POLLHUP

  std::weak_ptr<void> tie_;         //负责生存期？
  bool tied_;
  bool eventHandling_;              //是否正在处理事件
  bool addedToLoop_;                //是否已添加到eventloop中
  ReadEventCallback readCallBack_;
  EventCallback writeCallback_;
  EventCallback closeCallback_;
  EventCallback errorCallback_;
};

} // namespace net
}

#endif