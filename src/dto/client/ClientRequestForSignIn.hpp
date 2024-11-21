#ifndef __CLIENTREQUESTFORSIGNIN_H__
#define __CLIENTREQUESTFORSIGNIN_H__

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include "dto/citizen identify card/CitizenIdentifyCardDTO.h"
#include "entity/client/Client.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClientRequestForSignIn : public oatpp::DTO {
  DTO_INIT(ClientRequestForSignIn, DTO);

  DTO_FIELD(String, username);
  DTO_FIELD(String, password);
};
#include OATPP_CODEGEN_END(DTO)
#endif  // __CLIENTREQUESTFORSIGNIN_H__