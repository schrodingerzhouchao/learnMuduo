#ifndef MUDUO_BASE_DATE_H
#define MUDUO_BASE_DATE_H

#include <muduo/base/copyable.h>
#include <muduo/base/Types.h>

struct tm;

namespace muduo
{

// This class in immutable
// It's recommended to pass it by value, since it's passed in register on x64
// ?
class Date : public copyable
{
public:
  struct YearMonthDay
  {
      int year;
      int month;
      int day;
  };

  static const int kDaysPerWeak = 7;
  static const int kJulianDayOf1970_01_01;

  Date() : julianDayNumber_(0)
  {
  }
  explicit Date(int julianDayNum) : julianDayNumber_(julianDayNum)
  {
  }
  // yyyy-mm-dd
  Date(int year, int month, int day);

  explicit Date(const struct tm &);

  void swap(Date &that)
  {
    std::swap(julianDayNumber_, that.julianDayNumber_);
  }

  bool valid() const { return julianDayNumber_ > 0; }

  // converts to yyyy-mm-dd format
  string toIsoString() const;

  struct YearMonthDay yearMonthDay() const;

  int year() const
  {
    return yearMonthDay().year;
  }
  int month() const
  {
    return yearMonthDay().month;
  }
  int day() const
  {
    return yearMonthDay().day;
  }

  // 0123456 -> Sun. Mon. Tues. Wed. Thur. Fri. Sat.
  int weakDay() const
  {
    return (julianDayNumber_ + 1) % kDaysPerWeak;
  }

  int julianDayNumber() const { return julianDayNumber_; }

private:
  int julianDayNumber_;
};

inline bool operator<(Date x, Date y)
{
  return x.julianDayNumber() < y.julianDayNumber();
}
inline bool operator==(Date x, Date y)
{
  return x.julianDayNumber() == y.julianDayNumber();
}

} // namespace muduo

#endif