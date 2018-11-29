#include <muduo/base/Condition.h>

#include <cerrno>

// true if timeout
bool muduo::Condition::waitForSeconds(int seconds)
{
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += seconds;
    return ETIMEDOUT == pthread_cond_timedwait(&pcond_, mutex_.getPthreadMutex(), &abstime);    //  ETIMEDOUT Connection timed out ETIME?
}