#include <muduo/base/Logging.h>
#include <cerrno>

using namespace muduo;

int main()
{
    LOG_TRACE << "trace ...";
    LOG_DEBUG << "debug ...";
    LOG_INFO << "info ...";
    LOG_WARN << "warn ...";
    LOG_ERROR << "error ...";
    errno = 13;
    LOG_SYSERR << "syserr ...";
    LOG_SYSFATAL << "sysfatal ...";

    return 0;
}