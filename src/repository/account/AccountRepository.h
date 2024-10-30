#pragma once

#include <OracleQuery.h>

#include "entity/account/Account.h"
#include "entity/account/BasicAccount.h"

extern oracle::occi::Environment *g_obj_env;
extern oracle::occi::Connection *g_default_conn;

class AccountRepository : public OracleQuery<Account>
{
   public:
    AccountRepository(oracle::occi::Environment *env = g_obj_env, oracle::occi::Connection *conn = g_default_conn);
    std::optional<BasicAccount> get_basic_account_by_account_number_or_alias(const std::string_view &str);
};