#ifndef __MOVIECONTROLLER_H__
#define __MOVIECONTROLLER_H__

// oatpp

#include <memory>
#include <oatpp/macro/codegen.hpp>
#include <oatpp/macro/component.hpp>

#include "dto/ResponseDTO.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "temp/MovieDTO.hpp"
#include "temp/MovieService.hpp"

// service

#include OATPP_CODEGEN_BEGIN(ApiController)

class MovieController : public oatpp::web::server::api::ApiController {
 public:
  MovieController(OATPP_COMPONENT(
      std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMapper))
      : oatpp::web::server::api::ApiController(apiContentMapper, "movie") {}

  // ENDPOINT("GET", "", get_by_query,
  //          REQUEST(std::shared_ptr<IncomingRequest>, request)) {
  //   std::string tail = request->getPathTail();
  //   auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

  //   /* get your param by name */
  //   auto result =
  //       (temp) ? ResponseDTO::createShared(MovieDTO::createShared(temp.value()))
  //              : ResponseDTO::createShared(404, "Not Found");
  //   return createDtoResponse(Status(result->status_code, ""), result);
  // }

  

  ENDPOINT("GET", "/title", get_by_body, BODY_DTO(String, title)) {
    auto temp = MovieService::get(title);
    auto result =
        (temp) ? ResponseDTO::createShared(MovieDTO::createShared(temp.value()))
               : ResponseDTO::createShared(404, "Not Found");
    return createDtoResponse(Status(result->status_code, ""), result);
  }
};
#include OATPP_CODEGEN_END(ApiController)

#endif  // __MOVIECONTROLLER_H__