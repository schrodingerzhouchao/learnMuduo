#include <muduo/base/Thread.h>
#include <muduo/base/CurrentThread.h>
#include <muduo/base/Exception.h>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <cerrno>
#include <cstdio>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>

namespace muduo
{
namespace detail
{

pid_t gettid()
{
    return static_cast<pid_t>(::syscall(SYS_gettid));
}
void afterFork()
{
    muduo::CurrentThread::t_cachedTid = 0;
    muduo::CurrentThread::t_threadName = "main";
    CurrentThread::tid();
}

class ThreadNameInitializer
{
public:
  ThreadNameInitializer()
  {
      muduo::CurrentThread::t_threadName = "main";
      CurrentThread::tid();
      ::pthread_atfork(nullptr, nullptr, &afterFork); //  ? just child?   ==fork();exec();?
  }
};

ThreadNameInitializer init;
} // namespace detail
}

using namespace muduo;

void CurrentThread::cacheTid()
{
    if (t_cachedTid == 0)
    {
        t_cachedTid = detail::gettid();
        int n = snprintf(t_tidString, sizeof(t_tidString), "%5d ", t_cachedTid);
        assert(n == 6);
    }
}

bool CurrentThread::isMainThread()
{
    return tid() == ::getpid();
}

AtomicInt32 Thread::numCreated_;

Thread::Thread(const ThreadFunc &func, const string &name)
    : started_(false), pthreadId_(0), tid_(0), func_(func), name_(name)
{
    numCreated_.increment();
}

Thread::~Thread()
{
}

void Thread::start()
{
    assert(!started_);
    started_ = true;
    errno = ::pthread_create(&pthreadId_, nullptr, &startThread, this);
    if (errno != 0)
    {
        perror("pthread_create");
    }
}

int Thread::join()
{
    assert(started_);
    return ::pthread_join(pthreadId_, nullptr);
}

void *Thread::startThread(void *obj)
{
    Thread *thread = static_cast<Thread *>(obj);
    thread->runInThread();
    return nullptr;
}

void Thread::runInThread()
{
    tid_ = CurrentThread::tid();
    muduo::CurrentThread::t_threadName = name_.c_str();
    try
    {
        func_();
        muduo::CurrentThread::t_threadName = "finished";
    }
    catch (const Exception& e)
    {
        muduo::CurrentThread::t_threadName = "crashed";
        fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
        fprintf(stderr, "reason: %s\n", e.what());
        fprintf(stderr, "stack trace: %s\n", e.stackTrace());
        abort();
    }
    catch (const std::exception& e)
    {
        muduo::CurrentThread::t_threadName = "crashed";
        fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
        fprintf(stderr, "reason: %s\n", e.what());
        abort();
    }
    catch (...)
    {
        muduo::CurrentThread::t_threadName = "carashed";
        fprintf(stderr, "unknown exception caught in Thread %s\n", name_.c_str());
        throw;
    }
}