#ifndef __SIGNINCONTROLLER_H__
#define __SIGNINCONTROLLER_H__

#include "dto/ResponseDTO.hpp"
#include "dto/client/ClientRequestForSignIn.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "service/client/ClientService.h"

#include OATPP_CODEGEN_BEGIN(ApiController)  //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class SignInController : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param apiContentMappers - mappers used to serialize/deserialize DTOs.
   */
  SignInController(OATPP_COMPONENT(
      std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
      : oatpp::web::server::api::ApiController(apiContentMappers, "signin") {}

 public:
  ENDPOINT("GET", "/", sign_in,
           BODY_DTO(Object<ClientRequestForSignIn>, request)) {
    auto temp = service::ClientService::access_client(request->username,
                                                      request->password);
    auto result = ResponseDTO::createShared(temp);
    return createDtoResponse(Status(result->status_code, ""), result);
  }

  // TODO Insert Your endpoints here !!!
};

#include OATPP_CODEGEN_END(ApiController)  //<-- End Codegen

#endif  // __SIGNINCONTROLLER_H__