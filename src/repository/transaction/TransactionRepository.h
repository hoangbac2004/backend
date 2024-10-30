#pragma once

#include <OracleQuery.h>
#include <entity/transaction/Transaction.h>

extern oracle::occi::Environment* g_obj_env;
extern oracle::occi::Connection* g_default_conn;

class TransactionRepository : public OracleQuery<Transaction>
{
public:
	TransactionRepository(oracle::occi::Environment* env = g_obj_env, oracle::occi::Connection* conn = g_default_conn);
};