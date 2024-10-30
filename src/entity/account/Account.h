#pragma once

#include <occi.h>

class Account : public oracle::occi::PObject
{
   public:
    static constexpr const char* schema = "SYSTEM";
    static constexpr const char* type_name = "ACCOUNT";
    static constexpr const char* table_name = "ACCOUNT_TABLE";
    static constexpr const char* primary_key = "ACCOUNT_NUMBER";

    static oracle::occi::Environment* env;

    long long account_number;

    std::string bank;
    std::string name;
    std::string alias;
    double balance;

    Account() = default;
    template <typename T1, typename T2, typename T3>
    Account(long long account_number, T1&& bank, T2&& name, T3&& alias, double balance)
        : account_number(account_number),
          bank(std::forward<T1>(bank)),
          name(std::forward<T2>(name)),
          alias(std::forward<T3>(alias)),
          balance(balance)
    {
    }

    Account(const Account& other);
    Account(Account&& old) noexcept;

    Account& operator=(const Account& other);
    Account& operator=(Account&& old) noexcept;

    Account(void* ctxOCCI_);

    static void initialisation();
    void* operator new(size_t size);
    void* operator new(size_t size, const oracle::occi::Connection* sess, const OCCI_STD_NAMESPACE::string& table);
    void* operator new(size_t size, void* ctxOCCI_);
    void getSQLTypeName(oracle::occi::Environment* env, void** schemaName, unsigned int& schemaNameLen, void** typeName,
                        unsigned int& typeNameLen) const;
    virtual std::string getSQLTypeName() const;
    static void* readSQL(void* ctxOCCI_);
    virtual void readSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;
    static void writeSQL(void* objOCCI_, void* ctxOCCI_);
    virtual void writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;

    void set(const Account& old);
    void set(Account&& old);

    // transaction list;
};