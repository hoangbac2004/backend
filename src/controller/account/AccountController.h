#pragma once

#include <oatpp/macro/codegen.hpp>
#include <oatpp/macro/component.hpp>
#include <oatpp/web/server/api/ApiController.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController)

class AccountController : public oatpp::web::server::api::ApiController
{
public:
    AccountController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMapper))
        : oatpp::web::server::api::ApiController(apiContentMapper, "account")
    {
    }

    
};

#include OATPP_CODEGEN_END(ApiController)
