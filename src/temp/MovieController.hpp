#ifndef __MOVIECONTROLLER_H__
#define __MOVIECONTROLLER_H__

// oatpp
#include <memory>
#include <oatpp/macro/codegen.hpp>
#include <oatpp/macro/component.hpp>

#include "dto/ResponseDTO.hpp"
#include "oatpp/encoding/Url.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "temp/MovieDTO.hpp"
#include "temp/MovieService.hpp"

// service

#include OATPP_CODEGEN_BEGIN(ApiController)

class MovieController : public oatpp::web::server::api::ApiController {
 public:
  MovieController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>,
                                  apiContentMapper))
      : oatpp::web::server::api::ApiController(apiContentMapper, "movie") {}

  ENDPOINT("GET", "", get_by_body, QUERY(String, title)) {
    auto decoded = oatpp::encoding::Url::decode(title);
    auto temp = MovieService::get(decoded);
    if (temp.empty()) {
      return createDtoResponse(Status::CODE_404, ResponseDTO::createShared(404, "not found"));
    }
    auto result = oatpp::Vector<Object<MovieDTO>>::createShared();
    for (auto& element : temp) {
      result->emplace_back(MovieDTO::createShared(element));
    }
    return createDtoResponse(Status::CODE_200, ResponseDTO::createShared(result));
  }
};
#include OATPP_CODEGEN_END(ApiController)

#endif  // __MOVIECONTROLLER_H__