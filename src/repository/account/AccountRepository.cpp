#include "AccountRepository.h"

AccountRepository::AccountRepository(oracle::occi::Environment *env,
                                     oracle::occi::Connection *conn)
    : OracleQuery(env, conn) {}

std::optional<BasicAccount> AccountRepository::get_basic_account_by_account_number_or_alias(
    const std::string_view &str) {
  auto ref = execute_query_ref(
      std::format("SELECT REF(X) FROM {} WHERE ACCOUNT_NUMBER = '{}'",
                  Account::table_name, str));
  if (ref.isNull()) {
    ref = execute_query_ref(std::format("SELECT REF(X) FROM {} WHERE = '{}'",
                                        Account::table_name, str));
  }
  return ref.isNull()
             ? nullptr
             : std::make_optional<BasicAccount>(ref->account_number, ref->bank,
                                              ref->name, ref->alias);
}
