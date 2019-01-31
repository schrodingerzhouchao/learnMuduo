#include <muduo/base/Condition.h>
#include <time.h>
#include <cerrno>

// true if timeout
bool muduo::Condition::waitForSeconds(int seconds)
{
    struct timespec abstime;
    // CLOCK_REALTIME CLOCK_MONOTONIC e.g.
    clock_gettime(CLOCK_REALTIME, &abstime);    // -lrt
    const int64_t kNanoSecondsPerSecond = 1000000000;
    int64_t nanoseconds = static_cast<int64_t>(seconds * kNanoSecondsPerSecond);
    abstime.tv_sec += static_cast<time_t>((abstime.tv_nsec + nanoseconds) / kNanoSecondsPerSecond);
    abstime.tv_nsec = static_cast<long>((abstime.tv_nsec + nanoseconds) % kNanoSecondsPerSecond);

    // ETIMEOUT 110  connection timeout
    return ETIMEDOUT == pthread_cond_timedwait(&pcond_, mutex_.getPthreadMutex(), &abstime);
}