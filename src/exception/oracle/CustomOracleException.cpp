#include "./CustomOracleException.h"

CustomOracleException::CustomOracleException(int code)
{
    switch (code)
    {
        case 21527:
            messages = "overflow";
            break;
        default:
            messages = "unknown";
    }
}

const char* CustomOracleException::what() const noexcept { return messages.c_str(); }
