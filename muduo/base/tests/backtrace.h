
#ifndef BACKTRACE_H
#define BACKTRACE_H

#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <cxxabi.h>

// https://panthema.net/2008/0901-stacktrace-demangled/
// Print a demangled stack backtrace of the caller function to FILE* out.
static inline void print_stacktrace(FILE *out = stderr, unsigned int max_frames = 200)
{
    fprintf(out, "stack trace:\n");

    // storage array for stack trace address data
    void *addrlist[max_frames + 1];

    // retrieve current stack addresses
    int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void *));
    if (addrlen == 0)
    {
        fprintf(out, " <empty, possibly corrupt>\n");
        return;
    }

    // resolve addresses into string containing "filename(function+address)",
    // this array must be free()-ed
    char **symbollist = backtrace_symbols(addrlist, addrlen);

    // allocate string which will be filled with the demangled function name
    size_t funcnamesize = 256;
    char *funcname = reinterpret_cast<char *>(malloc(funcnamesize));

    // iterate over the returned symbol lines. skip the first, it is the
    // address of this function.
    for (int i = 0; i < addrlen; ++i)
    {
        printf("[%d]: %s\n", i,symbollist[i]);
        char *begin_name = nullptr, *begin_offset = nullptr, *end_offset = nullptr;

        // find parentheses and +address offset surrounding the mangled name:
        // ./module(function+0x15c) [ox8048a6d]
        for (char *p = symbollist[i]; *p; ++p)
        {
            if (*p == '('&&*(p+1)!='+')
                begin_name = p;
            else if (*p == '+')
                begin_offset = p;
            else if (*p == ')' && begin_offset)
            {
                end_offset = p;
                break;
            }
        }

        if (begin_name && begin_offset && end_offset && begin_name < begin_offset)
        {
            *begin_name++ = '\0';
            *begin_offset++ = '\0';
            *end_offset = '\0';

            // mangled name is now in [begin_name, begin_offset) and caller
            // offset in [begin_offset, end_offset). now apply
            // __cxa_demangle():
            
            // char* __cxa_demangle(const char* __mangled_name, 
            //                      char* __output_buffer, 
            //                      size_t* __length, 
            //                      int* __status);
            // __mangled_name \0
            // __output_buffer, __length, the demangled name stored in it
            // __status 0 = OK
            int status;
            char *ret = abi::__cxa_demangle(begin_name,
                                            funcname, &funcnamesize, &status);
            if (status == 0)
            {
                funcname = ret;
                fprintf(out, "  %s : %s+%s\n",
                        symbollist[i], funcname, begin_offset);
            }
            else
            {
                fprintf(out, "  %s\n", symbollist[i]);
            }
        }
    }

    free(funcname);
    free(symbollist);
}

#endif


