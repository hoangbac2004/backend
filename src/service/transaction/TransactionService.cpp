#include "TransactionService.h"

// #include "OracleQuery.h"

TransactionRepository service::TransactionService::query;

std::vector<Transaction> service::TransactionService::get_all() { return query.get_all(); }

std::optional<Transaction> service::TransactionService::get(long long id)
{
	return query.get(std::to_string(id));
}

std::string service::TransactionService::delete_by_id(long long id)
{
	CUSTOM_DEFAULT_QUERY(query.delete_by_primary_key(id));
}
