#ifndef MUDUO_BASE_LOGFILE_H
#define MUDUO_BASE_LOGFILE_H

#include <muduo/base/Mutex.h>
#include <muduo/base/Types.h>
#include <muduo/base/noncopyable.h>
#include <memory>

namespace muduo
{

class LogFile : noncopyable
{
public:
private:
  void append_unlocked(const char *logline, int len);
  static string getLogFileName(const string &basename, time_t *now);
  void rollFile();

  const string basename_;
  const size_t rollSize_;
  const int flushInterval_;

  int count_;

  std::unique_ptr<MutexLock> mutex_;
  time_t startOfPeriod_;
  time_t lastRoll_;
  time_t lastFLush_;
  class File;
  std::unique_ptr<File> file_;

  const static int kCheckTimeRoll_ = 1024;
  const static int kRollPerSeconds_ = 60 * 60 * 24;
};
} // namespace muduo

#endif