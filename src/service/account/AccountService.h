#pragma once

#include "define.h"

#include <memory>

#include "entity/account/Account.h"
#include "repository/account/AccountRepository.h"

namespace service::AccountService
{
extern AccountRepository query;
using Ref = oracle::occi::Ref<Account>;

std::vector<Account> get_all();
std::optional<Account> get(long long id);

std::string delete_by_id(long long id);

template <typename T>
std::string update(long long id, T &&obj)
{
  CUSTOM_DEFAULT_QUERY(query.update(id, std::forward<T>(obj)));
}

template <typename T>
std::string add(T &&obj)
{
  CUSTOM_DEFAULT_QUERY(query.add(std::format<T>(obj)));
}

std::optional<BasicAccount> get_basic_account_by_number_or_alias(const std::string_view &str);

}  // namespace service::AccountService
