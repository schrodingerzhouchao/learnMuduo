#ifndef MUDUO_BASE_MUTEX_H
#define MUDUO_BASE_MUTEX_H

#include <muduo/base/CurrentThread.h>
#include <muduo/base/noncopyable.h>
#include <cassert>
#include <pthread.h>


namespace muduo
{
class MutexLock : muduo::noncopyable
{
public:
  MutexLock() : holder_(0)
  {
      int ret = pthread_mutex_init(&mutex_, nullptr);
      assert(ret == 0);
  }
  ~MutexLock()
  {
      assert(holder_ == 0);
      int ret = pthread_mutex_destroy(&mutex_);
      assert(ret == 0);
  }

  bool isLockedByThisThread()
  {
      return holder_ == CurrentThread::tid();
  }
  
  void assertLocked()
  {
      assert(isLockedByThisThread());
  }

  void lock()
  {
      pthread_mutex_lock(&mutex_);
      holder_ = CurrentThread::tid();
  }
  void unlock()
  {
      holder_ = 0;
      pthread_mutex_unlock(&mutex_);
  }

  pthread_mutex_t* getPthreadMutex()
  {
      return &mutex_;
  }

private:
  pthread_mutex_t mutex_;
  pid_t holder_;
};


class MutexLockGuard : muduo::noncopyable
{
public:
  explicit MutexLockGuard(MutexLock &mutex) : mutex_(mutex)
  {
      mutex_.lock();
  }
  ~MutexLockGuard()
  {
      mutex_.unlock();
  }

private:
  MutexLock &mutex_;
};
} // namespace muduo


// A tempory object doesn't hold the lock for long
#define MutexLockGuard(x)  "Missing guard object name"     //  


#endif