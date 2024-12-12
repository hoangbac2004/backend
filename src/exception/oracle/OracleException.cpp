//
// Created by rog on 24/11/24.
//

#include "OracleException.h"

#include <utility>
const char* OracleException::what() const noexcept { return message.c_str(); }
OracleException::OracleException(std::string str) : message(std::move(str)) {}