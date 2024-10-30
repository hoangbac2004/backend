#pragma once

#include <occi.h>

#include <string>

#include "entity/account/Account.h"

class BasicAccount : public oracle::occi::PObject
{
   public:
    static constexpr const char* schema = "SYSTEM";
    static constexpr const char* type_name = "BASIC_ACCOUNT";
    static constexpr const char* table_name = "BASIC_ACCOUNT_TABLE";
    static constexpr const char* primary_key = "NUMBER";
    static oracle::occi::Environment* env;
    static void initialisation();

    long long account_number;
    std::string bank;
    std::string name;
    std::string alias;

    BasicAccount() = default;
    ~BasicAccount() = default;
    template <typename T1, typename T2, typename T3>
    BasicAccount(long long account_number, T1&& bank, T2&& name, T3&& alias = "")
        : account_number(account_number),
          bank(std::forward<T1>(bank)),
          name(std::forward<T2>(name)),
          alias(std::forward<T3>(alias))
    {
    }

    BasicAccount(const BasicAccount& other);
    BasicAccount(BasicAccount&& old) noexcept;
    BasicAccount& operator=(const BasicAccount& other);
    BasicAccount& operator=(BasicAccount&& old) noexcept;

    BasicAccount(const Account& account);
    BasicAccount& operator=(const Account& account);

    BasicAccount(void* ctxOCCI_);

    void* operator new(size_t size);
    void* operator new(size_t size, const oracle::occi::Connection* sess, const OCCI_STD_NAMESPACE::string& table);
    void* operator new(size_t size, void* ctxOCCI_);
    void getSQLTypeName(oracle::occi::Environment* env, void** schemaName, unsigned int& schemaNameLen, void** typeName,
                        unsigned int& typeNameLen) const;
    virtual std::string getSQLTypeName() const;
    static void* readSQL(void* ctxOCCI_);
    virtual void readSQL(oracle::occi::AnyData& streamOCCI_) noexcept;
    static void writeSQL(void* objOCCI_, void* ctxOCCI_);
    virtual void writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept;

    void set(const BasicAccount& old);
    void set(BasicAccount&& old);
};