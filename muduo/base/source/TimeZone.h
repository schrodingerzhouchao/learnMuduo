#ifndef MUDUO_BASE_TIMEZONE_H
#define MUDUO_BASE_TIMEZONE_H

#include <muduo/base/copyable.h>
#include <memory>
#include <time.h>

namespace muduo
{


class TimeZone : public copyable
{
public:
  explicit TimeZone(const char *zonefile);

  // Prior to 1972, the time was called Greenwich Mean Time(GMT) but is now referred to as Coordinated Universal Time or Universal Time Coordinated(UTC). Like UTC+8 大陆 东八区, UTC-10 夏威夷 西十区.
  TimeZone(int eastOfUtc, const char *tzname);
  TimeZone() = default;

  bool valid() const
  {
      // (bool)(data_) seems also work,
      // (data_==nullptr) -> true
      // PtrToBool.cpp in test
      return static_cast<bool>(data_);
  }

  struct tm toLocalTime(time_t secondsSinceEpoch) const;
  time_t fromLocalTime(const struct tm &) const;

  // gmtime transform data and time to broken-down time 
  static struct tm toUtcTime(time_t secondsSinceEpoch, bool yday = false);
  // timegm inverses of gmtime
  static time_t fromUtcTime(const struct tm &);

  static time_t fromUtcTime(int year, int month, int day, int hour, int minute, int seconds);
  
  struct Data;

private:
  std::shared_ptr<Data> data_;
};

} // namespace muduo

#endif  // MUDUO_BASE_TIMEZONE_H