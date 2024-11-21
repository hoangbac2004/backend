#pragma once

#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <type_traits>

#include "define.h"
// boost

#include <boost/date_time.hpp>

namespace tool {

std::string format_name(const std::string& input);
std::string format_date_time(const std::string& date);
std::string to_date_time(const std::string& date);
std::string from_tm_to_date(const std::tm& tm);

// template <typename T>
// std::enable_if_t<std::is_arithmetic_v<T>, std::optional<T>> get_random(const T min = std::numeric_limits<T>::min(),
//                                                                        const T max = std::numeric_limits<T>::max())
//{
//     if (min > max)
//     {
//         return std::nullopt;
//     }
//     std::uniform_int_distribution<T> dis(min, max);
//     return dis(gen);
// }
}  // namespace tool
