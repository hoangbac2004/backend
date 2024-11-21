#ifndef __CLIENTREQUEST_H__
#define __CLIENTREQUEST_H__

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include "dto/citizen identify card/CitizenIdentifyCardDTO.h"
#include "entity/client/Client.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClientRequest : public oatpp::DTO {
  DTO_INIT(ClientRequest, DTO);

  DTO_FIELD(Int64, number, "number");
  DTO_FIELD(String, username);
  DTO_FIELD(String, password);

  ClientRequest() = default;

 public:
  Client to_obj() { return Client(number, username, password); }
};
#include OATPP_CODEGEN_END(DTO)
#endif  // __CLIENTREQUEST_H__