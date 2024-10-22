#include "tool.h"
// Windows

// std
#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <random>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>


// boost
#include <boost/locale.hpp>

std::locale locale("vi_VN.UTF-8");

std::wstring tool::to_utf16(const std::string &input) { return boost::locale::conv::utf_to_utf<wchar_t>(input); }

std::string tool::to_utf8(const std::wstring &input) { return boost::locale::conv::utf_to_utf<char>(input); }

std::string tool::format_name(const std::string &input)
{
    std::wstring wstr = to_utf16(input);
    // delete redundant space at first and last

    auto is_not_space = [](wchar_t c) -> bool { return iswspace(c); };
    if (wstr.front() == ' ')
    {
        wstr.erase(wstr.begin(), std::ranges::find_if(wstr, is_not_space));
    }
    if (wstr.back() == ' ')
    {
        wstr.erase(std::ranges::find_last_if(wstr, is_not_space).begin() + 1, wstr.end());
    }
    // transform and delete space at middle

    bool is_capital = true;
    std::wstringstream swstr(std::move(wstr));
    std::wstring word;
    while (swstr >> word)
    {
        boost::algorithm::to_lower(word, locale);
        word.front() = std::toupper(word.front(), locale);
        wstr.append(word).append(L" ");
    }
    wstr.pop_back();
    return to_utf8(wstr);
}

std::string tool::format_date_time(const std::string &date_time)
{
    auto pos = std::ranges::find_if(date_time, ::isspace);
    if (pos == date_time.end())
    {
        // don't have time
        return boost::gregorian::to_iso_extended_string(boost::gregorian::from_simple_string(date_time));
    }
    else
    {
        auto result = boost::posix_time::to_iso_extended_string(boost::posix_time::time_from_string(date_time));
        result[10] = ' ';
        return result;
    }
}

std::string tool::to_date_time(const std::string& date)
{
    auto result = format_date_time(date);
    if (std::ranges::find(result, ' ') == result.end())
    {
        result.append(" 00:00:00");
    }
    return result;
}

std::string tool::from_tm_to_date(const std::tm& tm)
{
    auto temp = boost::gregorian::date_from_tm(tm);
    auto result = boost::gregorian::to_iso_extended_string(temp);
    return result;
}


