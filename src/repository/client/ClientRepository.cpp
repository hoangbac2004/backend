#include "ClientRepository.h"

#include <occi.h>

#include <format>

#include "entity/client/Client.h"
#include "exception/oracle/OracleException.h"

ClientRepository::ClientRepository(oracle::occi::Environment* env, oracle::occi::Connection* conn)
    : OracleQuery(env, conn) {}

// return execute_number_aggregate(std::format(
//     "SELECT COUNT(*) FROM {} WHERE username = '{}' AND password = '{}'",
//     Client::table_name, username, password)) > 0;
bool ClientRepository::find_username_and_password(const std::string& username,
                                                  const std::string& password) {
  // const auto temp = execute_query(std::format("SELECT * FROM {} WHERE USERNAME = '{}' AND
  // PASSWORD = '{}'",
  //                                       Client::table_name, username, password));
  CREATE_STATEMENT(std::format("SELECT * FROM {} WHERE USERNAME = '{}' AND PASSWORD = '{}'",
                               Client::table_name, username, password));
  std::cerr << stmt->getSQL() << std::endl;
  ResultSet* rs = stmt->executeQuery();
  if (rs->next()) {
    return true;
  }
  return false;
}
std::optional<Client> ClientRepository::get_client(const std::string& username,
                                                   const std::string& password) const {
  CREATE_STATEMENT(std::format("SELECT * FROM {} where USERNAME = '{}' AND PASSWORD = '{}'",
                               Client::table_name, username, password));
  ResultSet* rs = stmt->executeQuery();
  if (rs->next()) {
    return std::make_optional(Client(static_cast<long long>((double)rs->getNumber(1)),
      rs->getString(2), rs->getString(3)));
  } else {
    return std::nullopt;
  }
}
