#pragma once

#include <oatpp/macro/codegen.hpp>
#include <oatpp/macro/component.hpp>
#include <oatpp/web/server/api/ApiController.hpp>

#include "dto/ResponseDTO.hpp"
#include "dto/client/ClientRequest.h"
#include "dto/client/ClientResponse.h"
#include "service/client/ClientService.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class ClientController : public oatpp::web::server::api::ApiController {
 public:
  ClientController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMapper))
      : oatpp::web::server::api::ApiController(apiContentMapper, "client") {}

  ENDPOINT("POST", "/add", add, BODY_DTO(Object<ClientRequest>, request)) {
    return createResponse(Status::CODE_200, "");

  }

  ENDPOINT("GET", "/{id}", get, PATH(Int64, id)) {
    return createResponse(Status::CODE_200, "");
  }

  ENDPOINT("DELETE", "{id}", erase, PATH(Int64, id)) {
    return createResponse(Status::CODE_200, "");
  }
};

#include OATPP_CODEGEN_END(ApiController)