#pragma once

#include <memory>

#include "define.h"
#include "entity/client/Client.h"
#include "repository/client/ClientRepository.h"

namespace service::ClientService {
extern ClientRepository query;

std::vector<Client> get_all();
std::optional<Client> get(long long id);

std::string delete_by_id(long long id);

template <typename T>
std::string update(long long id, T&& obj) {
  CUSTOM_DEFAULT_QUERY(query.update(id, std::forward<T>(obj)));
}

template <typename T>
std::string add(T&& obj) {
  CUSTOM_DEFAULT_QUERY(query.add(std::forward<T>(obj)));
}
}  // namespace service::ClientService
