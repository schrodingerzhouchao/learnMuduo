#include <muduo/base/CurrentThread.h>
#include <cxxabi.h>
#include <execinfo.h>
#include <cstdlib>

namespace muduo
{
namespace CurrentThread
{
__thread int t_cachedTid = 0;
__thread char t_tidString[32];      //
__thread int t_tidStringLength = 6; //
__thread const char *t_threadName = "unknown";
static_assert(std::is_same<int, pid_t>::value, "pid_t should be int");  // why?

string stackTrace(bool demangle)
{
    string stack;
    const int max_frames = 200;
    void *frame[max_frames];
    //  (_Z3addi+0x1c) [0x...] like this
    int nptrs = ::backtrace(frame, max_frames);
    char **strings = ::backtrace_symbols(frame, nptrs);
    if(strings)
    {
        size_t len = 256;
        char *demangled = demangle ? static_cast<char *>(::malloc(len)) : nullptr;
        for (int i = 1; i < nptrs; ++i)
        {
            if(demangle)
            {
                char *left_par = nullptr;
                char *plus = nullptr;
                for (char *p = strings[i]; *p; ++p)
                {
                    if (*p == '(')
                        left_par = p;
                    else if (*p == '+')
                        plus = p;
                }

                if (left_par && plus)
                {
                    *plus = '\0';
                    int status = 0;
                    //  https://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html
                    char *ret = abi::__cxa_demangle(left_par + 1, demangled, &len, &status);
                    *plus = '+';
                    if (status == 0)
                    {
                        demangled = ret;
                        stack.append(strings[i], left_par + 1);
                        stack.append(demangled);
                        stack.append(plus);
                        stack.push_back('\n');
                        continue;
                    }
                }
            }
            stack.append(strings[i]);
            stack.push_back('\n');
        }
        free(demangled);
        free(strings);
    }
    return stack;
}

} // namespace CurrentThread
}