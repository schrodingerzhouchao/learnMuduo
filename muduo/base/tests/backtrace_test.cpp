#include "backtrace.h"
#include <map>

namespace Nu
{

template<typename Type>
struct Alpha
{
    struct Beta
    {
        void func()
        {
            print_stacktrace();
        }
        void func(Type)
        {
            print_stacktrace();
        }
    };
};

struct Gamma
{
    template<int N>
    void unroll(double d)
    {
        unroll<N - 1>(d);
    }
};

template<>
void Gamma::unroll<0>(double)
{
    print_stacktrace();
}

}

void print()
{
    printf("hello world\n");
    print_stacktrace();
}
int main()
{
    /*
    Nu::Alpha<int>::Beta().func(42);
    Nu::Alpha<char *>::Beta().func("42");
    Nu::Alpha<Nu::Alpha<std::map<int, double>>>::Beta().func();
    Nu::Gamma().unroll<5>(42.0);
    */
    print();

    return 0;
}