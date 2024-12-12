#pragma once

#include <memory>

#include "define.h"
#include "entity/account/Account.h"
#include "repository/account/AccountRepository.h"
#include "exception/oracle/OracleException.h"

namespace AccountService {
extern AccountRepository query;
using Ref = oracle::occi::Ref<Account>;

std::vector<Account> get_all();
std::optional<Account> get(long long id);

using string = std::string;
string delete_by_id(long long id);

template <typename T>
string update(long long id, T &&obj) {
  CUSTOM_DEFAULT_QUERY(query.update(id, std::forward<T>(obj)));
}

template <typename T>
string add(T &&obj) {
  CUSTOM_DEFAULT_QUERY(query.add(std::format<T>(obj)));
}

}  // namespace AccountService
