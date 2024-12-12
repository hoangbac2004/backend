#include "ClientService.h"

#include <occiControl.h>

#include <exception>

#include "define.h"

// #include "OracleQuery.h"

ClientRepository ClientService::query;

std::vector<Client> ClientService::get_all() { return query.get_all(); }

std::optional<Client> ClientService::get(long long id) { return query.get(std::to_string(id)); }

std::string ClientService::delete_by_id(long long id) {
  CUSTOM_DEFAULT_QUERY(query.delete_by_primary_key(id));
}

std::string ClientService::access_client(const std::string& username, const std::string& password) {
  try {
    return query.find_username_and_password(username, password) ? "" : "NO";
  } catch (const oracle::occi::SQLException& e) {
    return e.what();
  } catch (const std::exception& e) {
    return e.what();
  }
}
long long ClientService::get_id(const std::string& username, const std::string& password) {
  return (long long)query.execute_number_aggregate(
      std::format("select number_ from client_table where username = '{}' and password = '{}'",
                  username, password));
}
std::optional<Client> ClientService::get_by_username_and_password(const std::string& username,
                                                                  const std::string& password) {
  return query.get_client(username, password);
}

