#include "ClientRepository.h"

#include <format>

#include "entity/client/Client.h"

ClientRepository::ClientRepository(oracle::occi::Environment* env,
                                   oracle::occi::Connection* conn)
    : OracleQuery(env, conn) {}

bool ClientRepository::find_username_and_password(const std::string& username,
                                                  const std::string& password) {
  return execute_number_aggregate(std::format(
      "SELECT COUNT(*) FROM {} WHERE username = '{}' AND password = '{}'",
      Client::table_name, username, password)) > 0;
}
