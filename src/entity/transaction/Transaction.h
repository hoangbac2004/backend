#pragma once

#include <entity/account/BasicAccount.h>

#include <string>

class Transaction : public oracle::occi::PObject {
 public:
  static constexpr const short SUCCESSFUL = 2;
  static constexpr const short PROCESSING = 1;
  static constexpr const short FAILED = 0;
  static constexpr const char* schema = "SYSTEM";
  static constexpr const char* type_name = "ACCOUNT";
  static constexpr const char* table_name = "ACCOUNT_TABLE";
  static constexpr const char* primary_key = "ACCOUNT_NUMBER";
  static oracle::occi::Environment* env;

  BasicAccount from;
  BasicAccount to;
  double amount;
  std::string message;
  unsigned short state;

  template <typename T1, typename T2, typename T3>
  Transaction(T1&& from, T2&& to, double amount, T3&& message)
      : from(std::forward<T1>(from)),
        to(std::forward<T2>(to)),
        amount(amount),
        message(std::forward<T3>(message)),
        state(PROCESSING) {
  }

  template <typename T1, typename T2, typename T3>
  Transaction(T1&& from, T2&& to, double amount, T3&& message,
              unsigned short state)
      : from(std::forward<T1>(from)),
        to(std::forward<T2>(to)),
        amount(amount),
        message(std::forward<T3>(message)),
        state(state) {}

  Transaction(const Transaction& other);
  Transaction(Transaction&& old) noexcept;
  Transaction& operator=(const Transaction& other);
  Transaction& operator=(Transaction&& old) noexcept;

  Transaction(void* ctxOCCI_);

  static void initialisation();
  void* operator new(size_t size);
  void* operator new(size_t size, const oracle::occi::Connection* sess,
                     const OCCI_STD_NAMESPACE::string& table);
  void* operator new(size_t size, void* ctxOCCI_);
  void getSQLTypeName(oracle::occi::Environment* env, void** schemaName,
                      unsigned int& schemaNameLen, void** typeName,
                      unsigned int& typeNameLen) const;
  virtual std::string getSQLTypeName() const;
  static void* readSQL(void* ctxOCCI_);
  virtual void readSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;
  static void writeSQL(void* objOCCI_, void* ctxOCCI_);
  virtual void writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;

  void set(const Transaction& old);
  void set(Transaction&& old);

  void set_state(unsigned short state) { this->state = state; }
  void set_successful() { state = SUCCESSFUL; }
  void set_failed() { state = FAILED; }
};