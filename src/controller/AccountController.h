#pragma once

#include <oatpp/macro/codegen.hpp>
#include <oatpp/macro/component.hpp>
#include <oatpp/web/server/api/ApiController.hpp>

#include "dto/ResponseDTO.hpp"
#include "dto/account/AccountRequest.hpp"
#include "dto/account/AccountResponse.hpp"
#include "service/account/AccountService.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class AccountController : public oatpp::web::server::api::ApiController {
 public:
  AccountController(OATPP_COMPONENT(
      std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMapper))
      : oatpp::web::server::api::ApiController(apiContentMapper, "account") {}

  ENDPOINT("GET", "", get_with_not_sign_in,
           BODY_DTO(Object<AccountRequest>, request)) {
    auto temp =
        AccountService::get_basic_account_by_number_or_alias(request->input);
    return createDtoResponse(
        Status::CODE_200,
        temp.has_value()
            ? ResponseDTO::createShared(
                  AccountResponse::createShared(std::move(temp).value()))
            : ResponseDTO::createShared(404, "Not Found"));
  }

  // ENDPOINT("GET","/get" ,get_with_sign_in, BODY_DTO(Object<AccountRequest>, request)) {
  //   auto temp = AccountService::get_basic_account_by_number_or_alias(request->input);
  // }

};

#include OATPP_CODEGEN_END(ApiController)

