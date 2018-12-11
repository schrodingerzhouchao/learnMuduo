#include <pthread.h>
#include <iostream>
#include <sys/syscall.h>
#include <unistd.h>

using namespace std;

pthread_key_t key;

pid_t gettid()
{
    return static_cast<pid_t>(syscall(SYS_gettid));
}

void* thread1(void* arg)
{
    cout << "thread1 " << gettid() << " enter" << endl;
    int key_val = 10;
    pthread_setspecific(key, static_cast<void *>(&key_val));
    int *p = static_cast<int *>(pthread_getspecific(key));
    cout << "thread1 " << gettid() << " return the key_val " << *p << endl;
}

void* thread2(void* arg)
{
    cout << "thread2 " << gettid() << " enter" << endl;
    int key_val;
    if (arg == nullptr)
        key_val = 20;
    else
    {
        int *temp = static_cast<int *>(arg);
        key_val = *temp;
    }
    pthread_setspecific(key, static_cast<void *>(&key_val));
    int *p = static_cast<int*>(pthread_getspecific(key));
    cout << "thread2 " << gettid() << " return the key_val " << *p << endl;
}

int main()
{
    cout << "main thread " << gettid() << " is running" << endl;
    pthread_key_create(&key, nullptr);

    pthread_t t1, t2, t3;
    int x = 50;
    int *px = &x;
    pthread_create(&t1, nullptr, thread1, nullptr);
    pthread_create(&t2, nullptr, thread2, nullptr);
    pthread_create(&t3, nullptr, thread2, static_cast<void *>(px));
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);

    int key_val = 100;
    pthread_setspecific(key, static_cast<void *>(&key_val));
    int *p = static_cast<int *>(pthread_getspecific(key));
    cout << "main thread " << gettid() << " return " << *p << endl;
    
    pthread_key_delete(key);
    cout << "main thread exit" << endl;
    return 0;
}