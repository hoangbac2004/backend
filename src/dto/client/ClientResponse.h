#pragma once

// oatpp
#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

//
#include "entity/client/Client.h"

// DTO
#include "dto/citizen identify card/CitizenIdentifyCardDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClientResponse : public oatpp::DTO {
  DTO_INIT(ClientResponse, DTO);
  DTO_FIELD(Object<CitizenIdentifyCardDTO>, cic, "cic");

  ClientResponse() = default;

  template <typename T>
  ClientResponse(T&& obj) : cic(std::forward<T>(obj)) {}
};

#include OATPP_CODEGEN_END(DTO)