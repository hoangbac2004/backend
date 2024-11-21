#include "initialisation.h"

#include "data/personal information/CitizenIdentifyCard.h"
#include "entity/account/Account.h"
#include "entity/account/BasicAccount.h"
#include "entity/client/Client.h"
#include "entity/transaction/Transaction.h"

oracle::occi::Environment* g_obj_env =
    oracle::occi::Environment::createEnvironment(
        oracle::occi::Environment::OBJECT);
oracle::occi::Connection* g_default_conn =
    g_obj_env->createConnection("system", "0", "localhost:1521/oracle");

void initialisation::initialisation() {
  Account::initialisation();
  CitizenIdentifyCard::initialisation();
  Client::initialisation();
  BasicAccount::initialisation();
  Transaction::initialisation();
}
