#include "ClientRepository.h"

ClientRepository::ClientRepository(oracle::occi::Environment* env,
                                   oracle::occi::Connection* conn)
    : OracleQuery(env, conn) {}
