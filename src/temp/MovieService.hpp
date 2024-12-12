#pragma once

#include <optional>
#include <string>

#include "temp/MovieRepository.hpp"
namespace MovieService {
extern MovieRepository query;

inline std::vector<Movie> get(const std::string& title) {
  return query.get_by_title(title);
}
}  // namespace MovieService