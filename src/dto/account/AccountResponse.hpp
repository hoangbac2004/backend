#ifndef __ACCOUNTRESPONSE_H__
#define __ACCOUNTRESPONSE_H__

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)
class AccountResponse : public oatpp::DTO {
  DTO_INIT(AccountResponse, DTO);

  DTO_FIELD(Int64, account_number);
  DTO_FIELD(String, name);
  DTO_FIELD(String, alias);

  AccountResponse() = default;

  template <typename T1, typename T2, typename T3>
  AccountResponse(long long account_number, T1&& bank, T2&& name, T3&& alias)
      : account_number(account_number),
        name(std::forward<T2>(name)),
        alias(std::forward<T3>(alias)) {}

  template <typename T>
  AccountResponse(T&& account)
      : account_number(account.account_number),
        name(std::forward<T>(account).name),
        alias(std::forward<T>(account).alias) {}
};
#include OATPP_CODEGEN_END(DTO)

#endif  // __ACCOUNTRESPONSE_H__