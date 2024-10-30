#ifndef DTOs_hpp
#define DTOs_hpp

#include "oatpp/Types.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class MyDto : public oatpp::DTO {
  DTO_INIT(MyDto, DTO)

  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(String, message);

  // MyDto(std::string message = "", Int32 statusCode = 0) {
  //   this->message = message;   // Sử dụng this-> để gán giá trị
  //   this->statusCode = statusCode; // Sử dụng this-> để gán giá trị
  // }
  MyDto() = default;

  MyDto(int statusCode, std::string&& message) : statusCode(statusCode), message(std::move(message)) {}
};

#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */