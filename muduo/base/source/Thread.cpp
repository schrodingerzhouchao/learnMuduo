#include <muduo/base/Thread.h>
#include <muduo/base/CurrentThread.h>
#include <muduo/base/Exception.h>
//#include <muduo/base/Logging.h>
#include <muduo/base/CountDownLatch.h>
#include <muduo/base/Timestamp.h>

#include <type_traits>
#include <cerrno>
#include <cstdio>
#include <unistd.h>
#include <time.h>
#include <sys/prctl.h>
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
    //  -----------------
    //  ------fork-------       fork=>       ------lock1------lock2------
    //  --------lock1---- 
    //  -----------------
    //  --------lock2----                     no idea which thread hold which lock
    // pthread_atfork()
    muduo::CurrentThread::t_cachedTid = 0;
    muduo::CurrentThread::t_threadName = "main";
    CurrentThread::tid();                   // cacheTid() initialize t_cachedTid e.g.
}

class ThreadNameInitializer
{
public:
  ThreadNameInitializer()
  {
      muduo::CurrentThread::t_threadName = "main";
      CurrentThread::tid();
      // initialize child process(due to current thread call fork())     
      ::pthread_atfork(nullptr, nullptr, &afterFork);   
  }
};

ThreadNameInitializer init;     // initialize main thread.


struct ThreadData
{
    typedef Thread::ThreadFunc ThreadFunc;
    ThreadFunc func_;
    string name_;
    pid_t *tid_;
    CountDownLatch *latch_;

    ThreadData(ThreadFunc func,
               const string &name,
               pid_t *tid,
               CountDownLatch *latch)
        : func_(std::move(func)),
          name_(name),
          tid_(tid),
          latch_(latch)
    {
    }

    void runInThread()
    {
        *tid_ = CurrentThread::tid();   // catcheTid() -> __thread t_cachedTid
        tid_ = nullptr;                 // no needed  
        latch_->countDown();
        latch_ = nullptr;

        CurrentThread::t_threadName = name_.empty() ? "muduoThread" : name_.c_str();
        // PR_SET_NAME. Set the name of the calling thread, 16bytes long\0
        ::prctl(PR_SET_NAME, CurrentThread::t_threadName);  
        try
        {
            func_();
            CurrentThread::t_threadName = "finished";
        }
        catch (const Exception &ex)
        {
            CurrentThread::t_threadName = "crashed";
            fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
            fprintf(stderr, "reason: %s\n", ex.what());
            fprintf(stderr, "stack trace: %s\n", ex.stackTrace());
            abort();
        }
        catch (const std::exception &ex)
        {
            CurrentThread::t_threadName = "crashed";
            fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
            fprintf(stderr, "reason: %s\n", ex.what());
            abort();
        }
        catch (...)
        {
            CurrentThread::t_threadName = "crashed";
            fprintf(stderr, "unknown exception caught in Thread %s\n", name_.c_str());
            throw;
        }
    }
};

void *startThread(void *obj)        // pthread_create(,,,void *arg);
{
    ThreadData *data = static_cast<ThreadData *>(obj);
    data->runInThread();
    delete data;
    return nullptr;
}

} // namespace detail

void CurrentThread::cacheTid()
{
    if (t_cachedTid == 0)
    {
        t_cachedTid = detail::gettid();
        t_tidStringLength = snprintf(t_tidString, sizeof(t_tidString), "%5d", t_cachedTid);
    }
}

bool CurrentThread::isMainThread()
{
    return tid() == ::getpid();
}

void CurrentThread::sleepUsec(int64_t usec)
{
    struct timespec ts = {0, 0};
    ts.tv_sec = static_cast<time_t>(usec / Timestamp::kMicroSecondsPerSecond);
    ts.tv_nsec = static_cast<long>(usec % Timestamp::kMicroSecondsPerSecond * 1000);
    ::nanosleep(&ts, nullptr);
}

AtomicInt32 Thread::numCreated_;

Thread::Thread(ThreadFunc &func, const string &name)
    : started_(false),
      joined_(false),
      pthreadId_(0),
      tid_(0),
      func_(std::move(func)),
      name_(name),
      latch_(1)
{
    setDefaultName();
}

Thread::~Thread()
{
    if (started_ && !joined_)
    {
        pthread_detach(pthreadId_);
    }
}

void Thread::setDefaultName()
{
    int num = numCreated_.incrementAndGet();
    if (name_.empty())
    {
        char buf[32];
        snprintf(buf, sizeof(buf), "Thread%d", num);
        name_ = buf;
    }
}

void Thread::start()
{
    assert(!started_);
    started_ = true;
    detail::ThreadData *data = new detail::ThreadData(func_, name_, &tid_, &latch_);
    if (pthread_create(&pthreadId_, nullptr, &detail::startThread, data))
    {
        started_ = false;
        delete data;
        //LOG_SYSFATAL << "Failed in pthread_create()";
    }
    else
    {
        latch_.wait();
        assert(tid_ > 0);
    }
}

int Thread::join()
{
    assert(started_);
    assert(!joined_);
    joined_ = true;
    return ::pthread_join(pthreadId_, nullptr);
}

} // namespace detail