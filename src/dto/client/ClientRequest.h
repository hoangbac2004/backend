#pragma once

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include "dto/citizen identify card/CitizenIdentifyCardDTO.h"
#include "entity/client/Client.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClientRequest : public oatpp::DTO
{
    DTO_INIT(ClientRequest, DTO);

    DTO_FIELD(Int64, number, "number");
};
#include OATPP_CODEGEN_END(DTO)