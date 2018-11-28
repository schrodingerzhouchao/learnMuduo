#ifndef MUDUO_BASE_THREAD_H
#define MUDUO_BASE_THREAD_H

#include <muduo/base/Atomic.h>
#include <muduo/base/Types.h>
#include <muduo/base/noncopyable.h>

#include <boost/function.hpp>

#include <pthread.h>

namespace muduo
{
class Thread:muduo::noncopyable
{
public:
  typedef boost::function<void()> ThreadFunc;
  explicit Thread(const ThreadFunc &, const string &name = string());
  ~Thread();

  void start();
  int join();

  bool started() const { return started_; }
  pid_t tid() const { return tid_; }
  const string &name() const { return name_; }
  static int numCreated() { return numCreated_.get(); }

private:
  static void *startThread(void *thread);
  void runInThread();

  bool started_;
  pthread_t pthreadId_;
  pid_t tid_;
  ThreadFunc func_;
  string name_;
  static AtomicInt32 numCreated_;
};
} // namespace muduo
#endif