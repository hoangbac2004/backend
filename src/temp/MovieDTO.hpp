#ifndef DTOs_hpp
#define DTOs_hpp

#include "oatpp/Types.hpp"
#include "oatpp/macro/codegen.hpp"
#include "temp/Movie.hpp"
#include "tool.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class MovieDTO : public oatpp::DTO {
  DTO_INIT(MovieDTO, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, title);
  DTO_FIELD(String, release_date);
  DTO_FIELD(Float64, rating);
  DTO_FIELD(Int32, duration);
  DTO_FIELD(String, description);

  // MovieDTO(std::string message = "", Int32 statusCode = 0) {
  //   this->message = message;   // Sử dụng this-> để gán giá trị
  //   this->statusCode = statusCode; // Sử dụng this-> để gán giá trị
  // }
  MovieDTO() = default;

  MovieDTO(const Movie& movie)
      : id(movie.id),
        title(movie.title),
        release_date(tool::from_tm_to_date(movie.release_date)),
        rating(movie.rating),
        duration(movie.duration),
        description(movie.description) {}
};

#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */