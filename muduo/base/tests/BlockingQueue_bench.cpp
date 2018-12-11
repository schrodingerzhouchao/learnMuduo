#include <muduo/base/BlockingQueue.h>
#include <muduo/base/CountDownLatch.h>
#include <muduo/base/Thread.h>
#include <muduo/base/Timestamp.h>

#include <string>
#include <cstdio>
#include <map>
#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

class Bench
{
public:
  Bench(int numThreads) : latch_(numThreads), threads_(numThreads)
  {
      for (int i = 0; i < numThreads; ++i)
      {
          char name[32];
          snprintf(name, sizeof(name), "work thread %d", i);
          threads_.push_back(new muduo::Thread(boost::bind(&Bench::threadFunc, this), muduo::string(name)));
      }
      std::for_each(threads_.begin(), threads_.end(), boost::bind(&muduo::Thread::start, _1));
  }

  void run(int times)
  {
      printf("waiting for count down latch\n");
      latch_.wait();
      printf("all threads started\n");
      for (int i = 0; i < times; ++i)
      {
          muduo::Timestamp now(muduo::Timestamp::now());
          queue_.put(now);
          usleep(1000);
      }
  }

  void joinAll()
  {
      for (size_t i = 0; i < threads_.size(); ++i)
          queue_.put(muduo::Timestamp::invalid());
      std::for_each(threads_.begin(), threads_.end(), boost::bind(&muduo::Thread::join, _1));
  }

private:
  void threadFunc()
  {
      printf("threadFunc tid=%d, %s started\n",
             muduo::CurrentThread::tid(),
             muduo::CurrentThread::name());

      std::map<int, int> delays;
      latch_.countDown();
      bool running = true;
      while (running)
      {
          muduo::Timestamp t(queue_.take());
          muduo::Timestamp now(muduo::Timestamp::now());
          if (t.valid())
          {
              int delay = static_cast<int>(muduo::timeDifference(now, t) * 1000000);
              ++delays[delay];
          }
          running = t.valid();
      }

      printf("threadFunc tid=%d, %s stopped\n",
             muduo::CurrentThread::tid(),
             muduo::CurrentThread::name());
      for (auto it = delays.begin(); it != delays.end(); ++it)
          printf("threadFunc tid=%d, delay=%d, count=%d\n",
                 muduo::CurrentThread::tid(), it->first, it->second);
  }

  muduo::BlockingQueue<muduo::Timestamp> queue_;
  muduo::CountDownLatch latch_;
  boost::ptr_vector<muduo::Thread> threads_;
};

int main()
{
    Bench t(100);
    t.run(1000000);
    t.joinAll();

    return 0;
}