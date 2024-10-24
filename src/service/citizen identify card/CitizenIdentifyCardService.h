#pragma once

#include <optional>
#include <memory>
#include <vector>

#include "data/personal information/CitizenIdentifyCard.h"
#include "exception/oracle/CustomOracleException.h"
#include "repository/citizen identify card/CitizenIdentifyCardRepository.h"
#include "define.h"

namespace service::CitizenIdentifyCardService {
extern CitizenIdentifyCardRepository query;
using Ref = oracle::occi::Ref<CitizenIdentifyCard>;

std::vector<CitizenIdentifyCard> get_all();
std::optional<CitizenIdentifyCard> get(long long id);

std::string delete_by_id(long long id);

template <typename T>
std::string update(long long id, T&& obj) {
  CUSTOM_DEFAULT_QUERY(query.update(id, std::forward<T>(obj)));
}

template <typename T>
std::string add(T&& obj) {
  CUSTOM_DEFAULT_QUERY(query.add(std::forward<T>(obj)));
}
}  // namespace service::CitizenIdentifyCardService
