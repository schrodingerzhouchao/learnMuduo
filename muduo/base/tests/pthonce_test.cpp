#include <iostream>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>

using namespace std;

pthread_once_t ponce_ = PTHREAD_ONCE_INIT;

pid_t gettid()
{
    return static_cast<pid_t>(syscall(SYS_gettid));
}

void run_once(void)
{
    cout << "run_once in thread " << gettid() << endl;
}

void *thread1(void* arg)
{
    pid_t tid = gettid();
    cout << "thread1 " << tid << " enter" << endl;
    pthread_once(&ponce_, run_once);
    cout << "thread1 " << tid << " return" << endl;
}

void *thread2(void* arg)
{
    pid_t tid = gettid();
    cout << "thread2 " << tid << " enter" << endl;
    pthread_once(&ponce_, run_once);
    cout << "thread2 " << tid << " return" << endl;    
}

int main()
{
    pthread_t t1, t2;
    cout << "here we go" << endl;
    pthread_create(&t1, nullptr, thread1, nullptr);
    pthread_create(&t2, nullptr, thread2, nullptr);
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    cout << "main thread " << gettid() << " exit" << endl;

    return 0;
}