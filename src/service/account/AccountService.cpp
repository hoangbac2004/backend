#include "AccountService.h"

using AccountService::Ref;

AccountRepository AccountService::query;

std::vector<Account> AccountService::get_all() { return query.get_all(); }

std::optional<Account> AccountService::get(long long id) { return std::optional<Account>(); }

std::string AccountService::delete_by_id(long long id)
{
    CUSTOM_DEFAULT_QUERY(query.delete_by_primary_key(id));
}