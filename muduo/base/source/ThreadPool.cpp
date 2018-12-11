#include <muduo/base/ThreadPool.h>
#include <muduo/base/Exception.h>
#include <boost/bind.hpp>
#include <cassert>
#include <cstdio>

using namespace muduo;

ThreadPool::ThreadPool(const string &name)
    : mutex_(),
      cond_(mutex_),
      name_(name),
      running_(false)
{
}
ThreadPool::~ThreadPool()
{
    if (running_)
        stop();
}

void ThreadPool::start(int numThreads)
{
    assert(threads_.empty());
    running_ = true;
    threads_.reserve(numThreads);
    for (int i = 0; i < numThreads; ++i)
    {
        char id[32];
        snprintf(id, sizeof(id), "%d", i);
        threads_.push_back(new muduo::Thread(boost::bind(&ThreadPool::runInThread, this), name_ + id));
        threads_[i].start();
    }
}

void ThreadPool::stop()
{
    {
        MutexLockGuard lock(mutex_);
        running_ = false;
        cond_.notifyAll();
    }
    std::for_each(threads_.begin(), threads_.end(), boost::bind(&muduo::Thread::join, _1));
}

void ThreadPool::run(const Task& task)
{
    if (threads_.empty())
        task();
    else
    {
        MutexLockGuard lock(mutex_);
        queue_.push_back(task);
        cond_.notify();
    }
}

ThreadPool::Task ThreadPool::take()
{
    MutexLockGuard lock(mutex_);
    while (queue_.empty() && running_)
    {
        cond_.wait();
    }
    Task task;
    if (!queue_.empty())
    {
        task = queue_.front();
        queue_.pop_front();
    }
    return task;
}

void ThreadPool::runInThread()
{
    try
    {
        while (running_)
        {
            Task task(take());
            if (task)
            {
                task();
            }
        }
    }
    catch (const Exception& e)
    {
        fprintf(stderr, "exception caught in ThreadPool %s\n", name_.c_str());
        fprintf(stderr, "reason: %s\n", e.what());
        fprintf(stderr, "stack trace: %s\n", e.stackTrace());
        abort();
    }
    catch (const std::exception& e)
    {
        fprintf(stderr, "exception caught in ThreadPool %s\n", name_.c_str());
        fprintf(stderr, "reason: %s\n", e.what());
        abort();
    }
    catch (...)
    {
        fprintf(stderr, "unknown exception caught in ThreadPool %s\n", name_.c_str());
        throw;
    }
}

//取少量学生放入试管，加入过量作业，溶解过滤，得到学霸和学渣，分开放入试管中，加入试卷，学霸无明显变化，学渣则会溶解产生大量气泡，如想让学渣恢复原样，加入游戏即可。