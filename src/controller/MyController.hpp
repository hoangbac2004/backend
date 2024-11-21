#ifndef MyController_hpp
#define MyController_hpp

#include "dto/ResponseDTO.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "tool.h"

#include OATPP_CODEGEN_BEGIN(ApiController)  //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
public:
	/**
	 * Constructor with object mapper.
	 * @param apiContentMappers - mappers used to serialize/deserialize DTOs.
	 */
	MyController(OATPP_COMPONENT(
		std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
		: oatpp::web::server::api::ApiController(apiContentMappers) {}

public:
	ENDPOINT("GET", "/", root) {
	
		return createResponse(Status::CODE_200, Status::CODE_200.description);
	}

	// TODO Insert Your endpoints here !!!
};

#include OATPP_CODEGEN_END(ApiController)  //<-- End Codegen

#endif /* MyController_hpp */
