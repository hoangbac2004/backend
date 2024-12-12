#include "CitizenIdentifyCardService.h"


using CitizenIdentifyCardService::Ref;

CitizenIdentifyCardRepository CitizenIdentifyCardService::query;

std::vector<CitizenIdentifyCard> CitizenIdentifyCardService::get_all() { return query.get_all(); }

std::optional<CitizenIdentifyCard> CitizenIdentifyCardService::get(long long id) {
  return query.get(id);
}

std::string CitizenIdentifyCardService::delete_by_id(long long id) {
  CUSTOM_DEFAULT_QUERY(query.delete_by_primary_key(id));
}
