#pragma once

#include <occi.h>

#include <ctime>
#include <string>

class Date : public std::tm
{  // YYYY_MM-DD 24HH:MI:SS
   public:
    Date() = default;
    Date(const std::string& date);
    Date(const oracle::occi::Date& occiDate_);
    Date(int year, int month, int day, int hour, int minute, int second);
    ~Date() = default;

    Date(const Date& old);
    Date(Date&& old) noexcept;

    Date& operator=(const Date& old);
    Date& operator=(Date&& old) noexcept;

    oracle::occi::Date to_oracle_date(oracle::occi::Environment* env) const;
};