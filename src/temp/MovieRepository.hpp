#pragma once

#include "OracleQuery.h"
#include "temp/Movie.hpp"
extern oracle::occi::Environment *g_obj_env;
extern oracle::occi::Connection *g_default_conn;

class MovieRepository : public OracleQuery<Movie>
{
   public:
    MovieRepository(oracle::occi::Environment *env = g_obj_env,
                                  oracle::occi::Connection *conn = g_default_conn) : OracleQuery(env, conn) {}
};