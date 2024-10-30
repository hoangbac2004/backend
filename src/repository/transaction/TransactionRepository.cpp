#include "TransactionRepository.h"

TransactionRepository::TransactionRepository(oracle::occi::Environment* env, oracle::occi::Connection* conn)
	: OracleQuery(env, conn)
{
}
