//
// Created by rog on 24/11/24.
//

#ifndef ORACLEEXCEPTION_H
#define ORACLEEXCEPTION_H
#include <exception>
#include <string>

class OracleException : public std::exception {
  std::string message;
 public:
  [[nodiscard]] const char* what() const noexcept override;
  OracleException() = default;
  OracleException(std::string  str);
};



#endif //ORACLEEXCEPTION_H
