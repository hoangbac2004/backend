#pragma once

#include "define.h"
#include <memory>

#include "repository/transaction/TransactionRepository.h"

namespace service::TransactionService
{
extern TransactionRepository query;

std::vector<Transaction> get_all();
std::optional<Transaction> get(long long id);

std::string delete_by_id(long long id);

 template <typename T>
std::string update(long long id, T&& obj) {
  CUSTOM_DEFAULT_QUERY(query.update(id, std::forward<T>(obj)));
}

 template <typename T>
std::string add(T&& obj) {
  CUSTOM_DEFAULT_QUERY(query.add(std::forward<T>(obj)));
}
}  // namespace service::TransactionService

