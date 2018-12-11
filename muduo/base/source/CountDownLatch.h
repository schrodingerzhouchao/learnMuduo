#ifndef MUDUO_BASE_COUNTDOWNLATCH_H
#define MUDUO_BASE_COUNTDOWNLATCH_H

#include <muduo/base/Condition.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/noncopyable.h>

namespace muduo
{

class CountDownLatch : noncopyable
{
public:
  explicit CountDownLatch(int count);

  void wait();
  void countDown();
  int getCount() const;

private:
  mutable MutexLock mutex_;
  Condition condition_;
  int count_;
};

} // namespace muduo

#endif