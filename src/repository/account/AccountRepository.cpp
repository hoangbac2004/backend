#include "AccountRepository.h"

AccountRepository::AccountRepository(oracle::occi::Environment *env,
                                     oracle::occi::Connection *conn)
    : OracleQuery(env, conn) {}
