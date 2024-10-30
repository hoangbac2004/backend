#include "AccountService.h"

using service::AccountService::Ref;

AccountRepository service::AccountService::query;

std::vector<Account> service::AccountService::get_all() { return query.get_all(); }

std::optional<Account> service::AccountService::get(long long id) { return std::optional<Account>(); }

std::string service::AccountService::delete_by_id(long long id)
{
    CUSTOM_DEFAULT_QUERY(query.delete_by_primary_key(id));
}

std::optional<BasicAccount> service::AccountService::get_basic_account_by_number_or_alias(
    const std::string_view& str)
{
    return query.get_basic_account_by_account_number_or_alias(str);
}
