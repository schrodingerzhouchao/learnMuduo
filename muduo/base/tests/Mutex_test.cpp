#include <muduo/base/Mutex.h>
#include <muduo/base/Thread.h>
#include <muduo/base/Timestamp.h>

#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>
#include <cstdio>
#include <random>
#include <chrono>

muduo::MutexLock g_mutex;
std::vector<int> g_vec;
const int kCount = 10 * 1000 * 1000;

void threadFunc()
{
    for (int i = 0; i < kCount; ++i)
    {
        muduo::MutexLockGuard lock(g_mutex);
        g_vec.push_back(i);
    }
}

void displayRandomthElement()
{
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(1, kCount);
    int idx = distribution(generator);
    printf("%dth element is %d\n", idx-1, g_vec[idx-1]);
}

int main()
{
    const int kMaxThreads = 8;
    g_vec.reserve(kMaxThreads * kCount);

    muduo::Timestamp start(muduo::Timestamp::now());
    for (int i = 0; i < kCount; ++i)
    {
        g_vec.push_back(i);
    }
    printf("single thread without lock %f\n", muduo::timeDifference(muduo::Timestamp::now(), start));
    displayRandomthElement();

    start = muduo::Timestamp::now();
    threadFunc;
    printf("single thread with lock %f\n", muduo::timeDifference(muduo::Timestamp::now(), start));
    displayRandomthElement();

    for (int nthreads = 1; nthreads < kMaxThreads; ++nthreads)
    {
        boost::ptr_vector<muduo::Thread> threads;   // underlying std::vector<void*> to store the pointers
        g_vec.clear();
        start = muduo::Timestamp::now();
        /*
        for (int i = 0; i < nthreads; ++i)
        {
            threads.push_back(new muduo::Thread(&threadFunc));
            threads.back().start();
        }
        for (int i = 0; i < nthreads; ++i)
        {
            threads[i].join();
        }
        */

        threads.push_back(new muduo::Thread(&threadFunc));
        threads.back().start();
        threads[0].join();
        printf("%d thread(s) with lock %f\n", nthreads, muduo::timeDifference(muduo::Timestamp::now(), start));
        
        displayRandomthElement();
    }
    

    return 0;
}