#pragma once

#include <memory>
#include <oatpp/data/type/Object.hpp>

#include "define.h"
#include "entity/client/Client.h"
#include "exception/oracle/OracleException.h"
#include "repository/client/ClientRepository.h"

namespace ClientService {
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

std::string access_client(const std::string& username, const std::string& password);
long long get_id(const std::string& username, const std::string& password);

std::optional<Client> get_by_username_and_password(const std::string& username,
                                                   const std::string& password);
}  // namespace ClientService
