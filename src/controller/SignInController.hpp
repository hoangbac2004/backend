#pragma once

#include <oatpp/codegen/api_controller/cors_define.hpp>

#include "dto/ResponseDTO.hpp"
#include "dto/client/ClientRequestForSignIn.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "service/client/ClientService.h"

#include OATPP_CODEGEN_BEGIN(ApiController)  //<-- Begin Codegen
#include "service/citizen identify card/CitizenIdentifyCardService.h"

/**
 * Sample Api Controller.
 */
class SignInController : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param apiContentMappers - mappers used to serialize/deserialize DTOs.
   */
  SignInController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>,
                                   apiContentMappers))
      : oatpp::web::server::api::ApiController(apiContentMappers, "") {}

  ENDPOINT("POST", "/signin", sign_in, BODY_DTO(Object<ClientRequestForSignIn>, request)) {
    try
    {
      const auto temp =
         ClientService::get_by_username_and_password(request->username, request->password);
      if (!temp.has_value()) {
        return createDtoResponse(Status::CODE_401, ResponseDTO::createShared(401, "unathorized"));
      }
      const auto cic = CitizenIdentifyCardService::get(temp->number_);
      return createDtoResponse(Status::CODE_200,
                               ResponseDTO::createShared(CitizenIdentifyCardDTO::createShared(cic.value())));
    } catch (const std::exception& e) {
      return createDtoResponse(Status::CODE_404, ResponseDTO::createShared(404, e.what()));
    }
  }

  // TODO Insert Your endpoints here !!!
};

#include OATPP_CODEGEN_END(ApiController)  //<-- End Codegen
