#include "CitizenIdentifyCardService.h"


using service::CitizenIdentifyCardService::Ref;

CitizenIdentifyCardRepository service::CitizenIdentifyCardService::query;

std::vector<CitizenIdentifyCard> service::CitizenIdentifyCardService::get_all() { return query.get_all(); }

std::optional<CitizenIdentifyCard> service::CitizenIdentifyCardService::get(long long id) {
  return query.get(id);
}

std::string service::CitizenIdentifyCardService::delete_by_id(long long id) {
  CUSTOM_DEFAULT_QUERY(query.delete_by_primary_key(id));
}
