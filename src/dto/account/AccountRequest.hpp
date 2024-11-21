#ifndef __ACCOUNTREQUEST_H__
#define __ACCOUNTREQUEST_H__

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)
class AccountRequest : public oatpp::DTO {
  DTO_INIT(AccountRequest, DTO);

  DTO_FIELD(String, input);

  AccountRequest() = default;
  template <typename T1, typename T2>
  AccountRequest(T1&& input) : input(std::forward<T1>(input)){};
};

#include OATPP_CODEGEN_END(DTO)

#endif  // __ACCOUNTREQUEST_H__