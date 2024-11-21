#include "ClientService.h"
#include <occiControl.h>
#include <exception>

#include "define.h"

// #include "OracleQuery.h"

ClientRepository service::ClientService::query;

std::vector<Client> service::ClientService::get_all() {
  return query.get_all();
}

std::optional<Client> service::ClientService::get(long long id) {
  return query.get(std::to_string(id));
}

std::string service::ClientService::delete_by_id(long long id) {
  CUSTOM_DEFAULT_QUERY(query.delete_by_primary_key(id));
}

std::string service::ClientService::access_client(const std::string& username,
                                                  const std::string& password) {
  try {
    return query.find_username_and_password(username, password) ? "" : "NO";
  } catch (oracle::occi::SQLException &e) {
    return e.what();
  }
}
