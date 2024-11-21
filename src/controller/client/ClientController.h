#ifndef __CLIENTCONTROLLER_H__
#define __CLIENTCONTROLLER_H__

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
  ClientController(OATPP_COMPONENT(
      std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMapper))
      : oatpp::web::server::api::ApiController(apiContentMapper, "client") {}

  ENDPOINT("POST", "/add", add, BODY_DTO(Object<ClientRequest>, request)) {
    auto temp = service::ClientService::add(request->to_obj());
    auto result = ResponseDTO::createShared(temp);
    return createDtoResponse(Status(result->status_code, ""), result);
  }


  // ENDPOINT("DELETE", "{id}", erase, PATH(Int64, id)) {
  //   return createResponse(Status::CODE_200, "");
  // }

  ENDPOINT("PUT", "/update/{id}", update, PATH(Int64, id),
           BODY_DTO(Object<ClientRequest>, new_client)) {
    auto temp = service::ClientService::update(id, new_client->to_obj());
    auto result = ResponseDTO::createShared(temp);
    return createDtoResponse(Status(result->status_code, ""), result);
  }
};

#include OATPP_CODEGEN_END(ApiController)
#endif  // __CLIENTCONTROLLER_H__