#include "MovieService.hpp"
#include <format>
#include "temp/MovieRepository.hpp"

MovieRepository MovieService::query;

std::optional<Movie> MovieService::get(const std::string& sql) {
  return query.get_with_condition(std::format("WHERE title = '{}'", sql));
}
