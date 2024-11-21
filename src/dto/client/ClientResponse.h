#ifndef __CLIENTRESPONSE_H__
#define __CLIENTRESPONSE_H__

// oatpp
#include <format>
#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>
#include <utility>

//
#include "entity/client/Client.h"

// DTO
#include "dto/citizen identify card/CitizenIdentifyCardDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClientResponse : public oatpp::DTO {
  DTO_INIT(ClientResponse, DTO);
  DTO_FIELD(String, username, "username");
  DTO_FIELD(String, password, "password");

  ClientResponse() = default;

  template <typename T>
  ClientResponse(T&& obj)
      : username(std::forward<T>(obj).username), password(std::forward<T>(obj).password) {}
};

#include OATPP_CODEGEN_END(DTO)
#endif  // __CLIENTRESPONSE_H__