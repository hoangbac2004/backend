#include "initialisation.h"

#include "data/personal information/CitizenIdentifyCard.h"
#include "entity/account/Account.h"
#include "entity/client/Client.h"

oracle::occi::Environment* g_obj_env =
    oracle::occi::Environment::createEnvironment(
        oracle::occi::Environment::OBJECT);
oracle::occi::Connection* g_default_conn =
    g_obj_env->createConnection("system", "0", "localhost:1521/ORACLE");

void initialisation::initialisation() {
  g_obj_env->setCacheSortedFlush(true);
  Account::initialisation();
  CitizenIdentifyCard::initialisation();
  Client::initialisation();
}
