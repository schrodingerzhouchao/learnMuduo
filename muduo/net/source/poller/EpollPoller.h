#ifndef MUDUO_NET_POLLER_EPOLLPOLLER_H
#define MUDUO_NET_POLLER_EPOLLPOLLER_H

#include <muduo/net/Poller.h>

#include <map>
#include <vector>

struct epoll_event;

namespace muduo
{
namespace net
{

class EPollPoller : public Poller
{
public:
  EPollPoller(EventLoop *loop);
  ~EPollPoller() override;

  Timestamp poll(int timeoutMs, ChannelList *activeChannels) override;
  void updateChannel(Channel *channel) override;
  void removeChannel(Channel *channel) override;

private:
  static const int kInitEventListSize = 16;

  void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;
  void update(int operation, Channel *channel);

  typedef std::vector<struct epoll_event> EventList;
  typedef std::map<int, Channel *> ChannelMap;

  int epollfd_;
  EventList events_;
  ChannelMap channels_;
};

}
}

#endif