#pragma once

#include <exception>
#include <string>

class CustomOracleException : public std::exception
{
    std::string messages;

   public:
    explicit CustomOracleException(int code);

    template <typename T>
    explicit CustomOracleException(T&& messages = "") : messages(std::forward<T>(messages))
    {
    }

    const char* what() const noexcept override;
};