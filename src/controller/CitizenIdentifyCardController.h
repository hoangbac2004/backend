#ifndef __CITIZENIDENTIFYCARDCONTROLLER_H__
#define __CITIZENIDENTIFYCARDCONTROLLER_H__

// oatpp
#include <occiControl.h>

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>
#include <oatpp/macro/component.hpp>

#include "oatpp/web/server/api/ApiController.hpp"

// service

#include "service/citizen identify card/CitizenIdentifyCardService.h"

// dto
#include "dto/ResponseDTO.hpp"
#include "dto/citizen identify card/CitizenIdentifyCardDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class CitizenIdentifyCardController
    : public oatpp::web::server::api::ApiController {
 public:
  CitizenIdentifyCardController(OATPP_COMPONENT(
      std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMapper))
      : oatpp::web::server::api::ApiController(apiContentMapper, "cic") {}

  ENDPOINT("POST", "/create", create,
           BODY_DTO(Object<CitizenIdentifyCardDTO>, request)) {
    auto result = ResponseDTO::createShared(
        CitizenIdentifyCardService::add(request->to_obj()));
    return createDtoResponse(Status::CODE_200, result);
  }

  ENDPOINT("GET", "", get, QUERY(Int64, number)) {
    auto temp = CitizenIdentifyCardService::get(number);
    if (temp) {
      return createDtoResponse(
          Status::CODE_200,
          ResponseDTO::createShared(
              CitizenIdentifyCardDTO::createShared(std::move(temp).value())));
    } else {
      return createDtoResponse(Status::CODE_404,
                               ResponseDTO::createShared(404, "not found"));
    }
  }

  ENDPOINT("PUT", "/update/{number}", update, PATH(Int64, number),
           BODY_DTO(Object<CitizenIdentifyCardDTO>, new_obj)) {
    return createResponse(Status::CODE_200, "");
  }

  ENDPOINT("GET", "/all", get_all) {
    auto temp = 
        CitizenIdentifyCardService::get_all();
    auto dto = oatpp::Vector<Object<CitizenIdentifyCardDTO>>::createShared();
    for (auto& element : temp) {
      dto->push_back(CitizenIdentifyCardDTO::createShared(element));
    }    
    return createDtoResponse(Status::CODE_200, dto);
  }

  ENDPOINT("DELETE", "/delete/{number}", delete_, PATH(Int64, number)) {
    auto check = CitizenIdentifyCardService::delete_by_id(number);
    auto result = ResponseDTO::createShared(check);
    return createDtoResponse(Status(result->status_code, ""), result);
  }
};

#include OATPP_CODEGEN_END(ApiController)

#endif  // __CITIZENIDENTIFYCARDCONTROLLER_H__