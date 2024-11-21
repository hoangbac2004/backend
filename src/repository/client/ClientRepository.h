#pragma once

#include "entity/client/Client.h"
#include "OracleQuery.h"

extern oracle::occi::Environment* g_obj_env;
extern oracle::occi::Connection* g_default_conn;

class ClientRepository : public OracleQuery<Client>
{
   public:
    ClientRepository(oracle::occi::Environment* env = g_obj_env, oracle::occi::Connection* conn = g_default_conn);
    bool find_username_and_password(const std::string& username, const std::string& password);
};