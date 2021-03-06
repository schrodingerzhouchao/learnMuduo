#include <muduo/base/Date.h>
#include <cstdio>

namespace muduo
{

namespace detail
{

char require_32_bit_integer_at_least[sizeof(int) >= sizeof(int32_t) ? 1 : -1];

// Scaliger's Julian period starts on 1 Jan 4713 BC (Julian calendar) and lasts for 7980 years.
// After 7980 years the number starts from 1 again.
// In 4713 BC the Indiction, the Golden Number and the Solar Number were all 1, the next times
// this happens is 15*19*28=7980 years later, in AD 3268.
// example:
// at noon UT on 1 January AD 2000, JD 2,451,545 started.
// From 4713 BC to AD 2000 there are 6712 years (no 0000year)
// In the Julian calendar, years have 365.25 years, 365.25*6712=2,451,558days.
// Subtract from this the 13 days that the Gregorian calendar is ahead of the Julian calendar,
// 2,451,558 - 13 = 2,451,545days

int getJulianDayNumber(int year, int month, int day)
{
    (void)require_32_bit_integer_at_least;
    // Julian day number
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    // for a date in the Gregorian calendar
    return day + (153 * m + 2) / 5 + y * 365 + y / 4 - y / 100 + y / 400 - 32045;
    // for a date in the Julian calendar
    // day + (153 * m + 2) / 5 + y * 365 + y / 4 - 32045
}

struct Date::YearMonthDay getYearMonthDay(int julianDayNumber)
{
    int a = julianDayNumber + 32044;
    int b = (4 * a + 3) / 146097;
    int c = a - ((b * 146097) / 4);
    int d = (4 * c + 3) / 1461;
    int e = c - ((1461 * d) / 4);
    int m = (5 * e + 2) / 153;
    Date::YearMonthDay ymd;
    ymd.day = e - ((153 * m + 2) / 5) + 1;
    ymd.month = m + 3 - 12 * (m / 10);
    ymd.year = b * 100 + d - 4800 + (m / 10);
    return ymd;
}

} // namespace detail

const int Date::kJulianDayOf1970_01_01 = detail::getJulianDayNumber(1970, 1, 1);

} // namespace muduo

using namespace muduo;
using namespace muduo::detail;

Date::Date(int y, int m, int d)
    : julianDayNumber_(getJulianDayNumber(y, m, d))
{
}

Date::Date(const struct tm &t)
    : julianDayNumber_(getJulianDayNumber(
          t.tm_year + 1900,
          t.tm_mon + 1,
          t.tm_mday))
{
}

Date::YearMonthDay Date::yearMonthDay() const
{
    return getYearMonthDay(julianDayNumber_);
}
string Date::toIsoString() const
{
    char buf[32];
    YearMonthDay ymd(yearMonthDay());
    snprintf(buf, sizeof(buf), "%4d-%02d-%02d", ymd.year, ymd.month, ymd.day);
    return buf;
}
