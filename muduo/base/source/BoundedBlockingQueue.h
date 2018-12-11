#ifndef MUDUO_BASE_BOUNDEDBLOCKINGQUEUE_H
#define MUDUO_BASE_BOUNDEDBLOCKINGQUEUE_H

#include <muduo/base/Condition.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/noncopyable.h>

#include <boost/circular_buffer.hpp>
#include <cassert>

namespace muduo
{

template <typename T>
class BoundedBlockingQueue : noncopyable
{
public:
  explicit BoundedBlockingQueue(int maxSize)
      : mutex_()
      , notEmpty_(mutex_)
      , notFull_(mutex_)
      , queue_(maxSize)
  {
  }

  void put(const T &x)
  {
      MutexLockGuard lock(mutex_);
      while (queue_.full())
          notFull_.wait();      // waiting take() to take something
      assert(!queue_.full());
      queue_.push_back(x);
      notEmpty_.notify();       // tell take() can take
  }
  T take()
  {
      MutexLockGuard lock(mutex_);
      while (queue_.empty())
          notEmpty_.wait();     // waiting put() to put something into queue_
      assert(!queue_.empty());
      T front(queue_.front());
      queue_.pop_front();
      notFull_.notify();       // tell put() can put
      return front;
  }

  bool empty() const
  {
      MutexLockGuard lock(mutex_);
      return queue_.empty();
  }
  bool full() const
  {
      MutexLockGuard lock(mutex_);
      return queue_.full();
  }

  size_t size() const
  {
      MutexLockGuard lock(mutex_);
      return queue_.size();
  }
  size_t capacity() const
  {
      MutexLockGuard lock(mutex_);
      return queue_.capacity();
  }

private:
  mutable MutexLock mutex_;
  Condition notEmpty_;
  Condition notFull_;
  boost::circular_buffer<T> queue_;
};

} // namespace muduo

#endif