#ifndef MUDUO_BASE_SINGLETON_H
#define MUDUO_BASE_SINGLETON_H

#include <muduo/base/noncopyable.h>
#include <pthread.h>
#include <cstdlib>

namespace muduo
{

template <typename T>
class Singleton : noncopyable
{
public:
  static T &instance()
  {
      pthread_once(&ponce_, &Singleton::init);
      return *value_;
  }

private:
  Singleton();
  ~Singleton();

  static void init()
  {
      value_ = new T();
      ::atexit(destroy);
  }

  static void destroy()
  {
      typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
      delete value_;
  }

private:
  static pthread_once_t ponce_;
  static T *value_;
};

template <typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template <typename T>
T *Singleton<T>::value_ = nullptr;

} // namespace muduo

#endif