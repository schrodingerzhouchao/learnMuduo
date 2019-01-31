#ifndef MUDUO_BASE_CURRENTTHREAD_H
#define MUDUO_BASE_CURRENTTHREAD_H

#include <muduo/base/Types.h>

namespace muduo
{
namespace CurrentThread
{
extern __thread int t_cachedTid;
extern __thread char t_tidString[32];
extern __thread int t_tidStringLength;
extern __thread const char *t_threadName;
void cacheTid();    // in Thread.cpp

inline int tid()
{
    // long __builtin_expect(long exp, long c)
    // the idea of __builtin_expect is to tell the compiler that you'll ususally find
    // that the expression evaluates to c, so that the compiler can optimize for that
    // case.
    if (__builtin_expect(t_cachedTid == 0, 0))
        cacheTid();
    return t_cachedTid;
}
inline const char* tidString()      // for logging
{
    return t_tidString;
}
inline int tidStringLength()        // for logging
{
    return t_tidStringLength;
}
inline const char* name()
{
    return t_threadName;
}

bool isMainThread();                // in Thread.cpp

void sleepUsec(int64_t usec);       // in Thread.cpp for testing

// mangle&demangle
// mangle   original c++ source identifier -> c++ ABI identifier
// demangle                                <-
string stackTrace(bool demangle);   


} // namespace CurrentThread
} // namespace muduo
#endif
