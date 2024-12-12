#pragma once

#include <OracleQuery.h>

#include "entity/account/Account.h"

extern oracle::occi::Environment *g_obj_env;
extern oracle::occi::Connection *g_default_conn;

class AccountRepository : public OracleQuery<Account>
{
   public:
    explicit AccountRepository(oracle::occi::Environment *env = g_obj_env, oracle::occi::Connection *conn = g_default_conn);
};