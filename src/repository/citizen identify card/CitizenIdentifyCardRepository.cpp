#include "CitizenIdentifyCardRepository.h"

CitizenIdentifyCardRepository::CitizenIdentifyCardRepository(
    oracle::occi::Environment *env, oracle::occi::Connection *conn)
    : OracleQuery(env, conn) {}
