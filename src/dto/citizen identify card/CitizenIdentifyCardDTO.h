#ifndef __CITIZENIDENTIFYCARDDTO_H__
#define __CITIZENIDENTIFYCARDDTO_H__

#include <data/personal information/CitizenIdentifyCard.h>
#include <tool.h>

#include <iostream>
#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class CitizenIdentifyCardDTO : public oatpp::DTO {
  DTO_INIT(CitizenIdentifyCardDTO, DTO);

  DTO_FIELD(Int64, number, "number");
  DTO_FIELD(String, full_name, "fullName");
  DTO_FIELD(String, date_of_birth, "dateOfBirth");
  DTO_FIELD(String, sex, "sex");
  DTO_FIELD(String, nationality, "nationality");
  DTO_FIELD(String, place_of_origin, "placeOfOrigin");
  DTO_FIELD(String, place_of_residence, "placeOfResidence");
  DTO_FIELD(String, date_of_expiry, "dateOfExpiry");

  CitizenIdentifyCardDTO() = default;

  template <typename T>
  CitizenIdentifyCardDTO(T&& obj)
      : number(obj.number),
        full_name(std::forward<T>(obj).full_name),
        date_of_birth(tool::from_tm_to_date(obj.date_of_birth)),
        sex(std::forward<T>(obj).sex),
        nationality(std::forward<T>(obj).nationality),
        place_of_origin(std::forward<T>(obj).place_of_origin),
        place_of_residence(std::forward<T>(obj).place_of_residence),
        date_of_expiry(tool::from_tm_to_date(obj.date_of_expiry)) {}

 public:
  CitizenIdentifyCard to_obj() {
    return CitizenIdentifyCard(
        number, full_name, std::move(date_of_birth), std::move(sex),
        std::move(nationality), std::move(place_of_origin),
        std::move(place_of_residence), std::move(date_of_expiry));
  }
};

#include OATPP_CODEGEN_END(DTO)
#endif  // __CITIZENIDENTIFYCARDDTO_H__