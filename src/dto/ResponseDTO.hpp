#ifndef __RESPONSEDTO_H__
#define __RESPONSEDTO_H__


#include "oatpp/Types.hpp"
#include "oatpp/macro/codegen.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class ResponseDTO : public oatpp::DTO {
  DTO_INIT(ResponseDTO, DTO);

  DTO_FIELD(Int16, status_code, "statusCode") = 200;
  DTO_FIELD(String, message) = "success";
  DTO_FIELD(Any, data);

 public:
  ResponseDTO() = default;

  ResponseDTO(int16_t status_code, std::string&& message)
      : status_code(status_code), message(message.empty() ? "success" : std::move(message)) {}

  ResponseDTO(int16_t status_code, const std::string& message)
      : status_code(status_code), message(message.empty() ? "success" : message) {}

  ResponseDTO(Any&& data) : status_code(200), message("success"), data(std::move(data)) {}

  ResponseDTO(const Any& data) : status_code(200), message("success"), data(data) {}

  ResponseDTO(std::string&& message)
      : status_code(message.empty() ? 200 : 404), message(message.empty() ? "success" : std::move(message)) {}

  ResponseDTO(const std::string& message)
      : status_code(message.empty() ? 200 : 404), message(message.empty() ? "success" : message) {}

};

#include OATPP_CODEGEN_END(DTO)

#endif // __RESPONSEDTO_H__