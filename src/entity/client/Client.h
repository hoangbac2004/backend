#pragma once

#include <vector>

//
#include <data/personal information/CitizenIdentifyCard.h>
#include <occi.h>

#include <string>

class Client : public oracle::occi::PObject
{
   public:
    static constexpr const char* schema = "SYSTEM";
    static constexpr const char* type_name = "CLIENT";
    static constexpr const char* table_name = "CLIENT_TABLE";
    static constexpr const char* primary_key = "NUMBER";

    static oracle::occi::Environment* env;
    
    //OneToOne
    CitizenIdentifyCard CIC;
    std::string username;
    std::string password;

    template <typename T1, typename T2, typename T3>
    Client(T1&& CIC, T2&& username, T3&& password);
    // get account management
    Client(const Client& other);
    Client(Client&& old) noexcept;

    Client& operator=(const Client& other);
    Client& operator=(Client&& other) noexcept;
    Client(void* ctxOCCI_);

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

    void set(const Client& old);
    void set(Client&& old);
};

template <typename T1, typename T2, typename T3>
inline Client::Client(T1&& CIC, T2&& username, T3&& password)
    : CIC(std::forward<T1>(CIC)), username(std::forward<T2>(username)), password(std::forward<T3>(password))
{
}
