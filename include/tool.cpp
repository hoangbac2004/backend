#include "tool.h"
// Windows

// std
#include <unicode/unistr.h>
#include <unicode/ustream.h>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <semaphore>
#include <sstream>
#include <string>

// boost
#include <boost/locale.hpp>

std::string tool::format_name(const std::string& input) {
  std::string result;
  result.reserve(input.size());

  // remove redundant space
  std::istringstream input_stream(input);
  std::string temp;
  while (input_stream >> temp) {
    result += temp + ' ';
  }
  result.pop_back();
  auto unicode_string = icu::UnicodeString{result.c_str()};
  result.clear();
  unicode_string.toTitle(nullptr).toUTF8String(result);
  return result;
}

std::string tool::format_date_time(const std::string& date_time) {
  auto pos = std::ranges::find_if(date_time, ::isspace);
  if (pos == date_time.end()) {
    // don't have time
    return boost::gregorian::to_iso_extended_string(
        boost::gregorian::from_simple_string(date_time));
  } else {
    auto result = boost::posix_time::to_iso_extended_string(
        boost::posix_time::time_from_string(date_time));
    result[10] = ' ';
    return result;
  }
}

std::string tool::to_date_time(const std::string& date) {
  auto result = format_date_time(date);
  if (std::ranges::find(result, ' ') == result.end()) {
    result.append(" 00:00:00");
  }
  return result;
}

std::string tool::from_tm_to_date(const std::tm& tm) {
  auto temp = boost::gregorian::date_from_tm(tm);
  auto result = boost::gregorian::to_iso_extended_string(temp);
  return result;
}
