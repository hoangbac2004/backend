#pragma once

// lib
#include "data/personal information/CitizenIdentifyCard.h"
#include "OracleQuery.h"

extern oracle::occi::Environment *g_obj_env;
extern oracle::occi::Connection *g_default_conn;

class CitizenIdentifyCardRepository : public OracleQuery<CitizenIdentifyCard>
{
   public:
    CitizenIdentifyCardRepository(oracle::occi::Environment *env = g_obj_env,
                                  oracle::occi::Connection *conn = g_default_conn);
};