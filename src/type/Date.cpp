#include "Date.h"

#include <sstream>
#include <string>

#include "tool.h"

Date::Date(const std::string& date)
{
    auto tm = boost::posix_time::to_tm(boost::posix_time::time_from_string(tool::to_date_time(date)));
    tm_year = tm.tm_year;
    tm_mon = tm.tm_mon;
    tm_mday = tm.tm_mday;
    tm_hour = tm.tm_hour;
    tm_min = tm.tm_min;
    tm_sec = tm.tm_sec;
}

Date::Date(const oracle::occi::Date& occiDate_)
{
    int year;
    unsigned month, day, hour, minute, second;
    occiDate_.getDate(year, month, day, hour, minute, second);
    tm_year = year - 1900;
    tm_mon = month - 1;
    tm_mday = day;
    tm_hour = hour;
    tm_min = minute;
    tm_sec = second;
}

Date::Date(const Date& old) : std::tm{old.tm_sec, old.tm_min, old.tm_hour, old.tm_mday, old.tm_mon, old.tm_year} {}

Date::Date(Date&& old) noexcept : std::tm{old.tm_sec, old.tm_min, old.tm_hour, old.tm_mday, old.tm_mon, old.tm_year} {}

Date& Date::operator=(const Date& old)
{
    if (this == &old)
    {
        return *this;
    }
    tm_year = old.tm_year;
    tm_mon = old.tm_mon;
    tm_mday = old.tm_mday;
    tm_hour = old.tm_hour;
    tm_min = old.tm_min;
    tm_sec = old.tm_sec;
    return *this;
}

Date& Date::operator=(Date&& old) noexcept
{
    if (this == &old)
    {
        return *this;
    }
    tm_year = old.tm_year;
    tm_mon = old.tm_mon;
    tm_mday = old.tm_mday;
    tm_hour = old.tm_hour;
    tm_min = old.tm_min;
    tm_sec = old.tm_sec;
    return *this;
}

Date::Date(int year, int month, int day, int hour, int minute, int second)
{
    tm_year = year - 1900;
    tm_mon = month - 1;
    tm_mday = day;
    tm_hour = hour;
    tm_min = minute;
    tm_sec = second;
}

oracle::occi::Date Date::to_oracle_date(oracle::occi::Environment* env) const
{
    return oracle::occi::Date(env, tm_year + 1900, tm_mon + 1, tm_mday, tm_hour, tm_min, tm_sec);
}
