#pragma once

#include <optional>
#include <string>

#include "temp/MovieRepository.hpp"
namespace MovieService {
extern MovieRepository query;

std::optional<Movie> get(const std::string& sql);
}  // namespace MovieService