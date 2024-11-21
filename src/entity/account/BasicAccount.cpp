#include "BasicAccount.h"

// std
#include <format>
#include <iostream>

//
#include "service/account/AccountService.h"

oracle::occi::Environment* BasicAccount::env = nullptr;

void BasicAccount::initialisation()
{
    extern oracle::occi::Environment* g_obj_env;
    env = g_obj_env;
}

BasicAccount::BasicAccount(const BasicAccount& other)
    : account_number(other.account_number), bank(other.bank), name(other.name), alias(other.alias)
{
}

BasicAccount::BasicAccount(BasicAccount&& old) noexcept
    : account_number(old.account_number),
      bank(std::move(old.bank)),
      name(std::move(old.name)),
      alias(std::move(old.alias))
{
}
 
BasicAccount& BasicAccount::operator=(const BasicAccount& other)
{
    if (this == &other)
    {
        return *this;
    }
    account_number = other.account_number;
    bank = other.bank;
    name = other.name;
    alias = other.alias;
    return *this;
}

BasicAccount& BasicAccount::operator=(BasicAccount&& old) noexcept
{
    if (this == &old)
    {
        return *this;
    }
    account_number = old.account_number;
    bank = std::move(old.bank);
    name = std::move(old.name);
    alias = std::move(old.alias);
    return *this;
}

BasicAccount::BasicAccount(const Account& account)
    : account_number(account.account_number), bank(account.bank), name(account.name), alias(account.alias)
{
}

BasicAccount& BasicAccount::operator=(const Account& account)
{
    account_number = account.account_number;
    bank = account.bank;
    name = account.name;
    alias = account.alias;
    return *this;
}

BasicAccount::BasicAccount(void* ctxOCCI_) : oracle::occi::PObject(ctxOCCI_) {}

void* BasicAccount::operator new(size_t size) { return oracle::occi::PObject::operator new(size); }

void* BasicAccount::operator new(size_t size, const oracle::occi::Connection* sess,
                                 const OCCI_STD_NAMESPACE::string& table)
{
    return oracle::occi::PObject::operator new(size, sess, table, std::format("{}.{}", schema, type_name).c_str());
}

void* BasicAccount::operator new(size_t size, void* ctxOCCI_)
{
    return oracle::occi::PObject::operator new(size, ctxOCCI_);
}

void BasicAccount::getSQLTypeName(oracle::occi::Environment* env, void** schemaName, unsigned int& schemaNameLen,
                                  void** typeName, unsigned int& typeNameLen) const
{
    return oracle::occi::PObject::getSQLTypeName(env, &BasicAccount::readSQL, schemaName, schemaNameLen, typeName,
                                                 typeNameLen);
}

std::string BasicAccount::getSQLTypeName() const { return table_name; }

void* BasicAccount::readSQL(void* ctxOCCI_)
{
    BasicAccount* objOCCI_ = new (ctxOCCI_) BasicAccount(ctxOCCI_);
    oracle::occi::AnyData streamOCCI_(ctxOCCI_);
    try
    {
        if (streamOCCI_.isNull())
        {
            objOCCI_->setNull();
        }
        else
        {
            objOCCI_->readSQL(streamOCCI_);
        }
    }
    catch (oracle::occi::SQLException& e)
    {
        delete objOCCI_;
        e.setErrorCtx(ctxOCCI_);
        std::cerr << e.what() << std::endl;
        return (void*)nullptr;
    }
    return (void*)objOCCI_;
}

void BasicAccount::readSQL(oracle::occi::AnyData& streamOCCI_) noexcept
{
    std::string number_or_alias = streamOCCI_.getString();
    streamOCCI_.getString();
    *this = std::move(*service::AccountService::get_basic_account_by_number_or_alias(number_or_alias));
}

void BasicAccount::writeSQL(void* objOCCI_, void* ctxOCCI_)
{
    BasicAccount* objectOCCI_ = (BasicAccount*)objOCCI_;
    oracle::occi::AnyData streamOCCI_(ctxOCCI_);
    try
    {
        if (objectOCCI_->isNull())
        {
            streamOCCI_.setNull();
        }
        else
        {
            objectOCCI_->writeSQL(streamOCCI_);
        }
    }
    catch (oracle::occi::SQLException& e)
    {
        e.setErrorCtx(ctxOCCI_);
        std::cerr << e.what() << std::endl;
    }
}

void BasicAccount::writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept 
{
    std::string number_or_alias = account_number == 0 ? alias : std::to_string(account_number);
    streamOCCI_.setString(number_or_alias);
    streamOCCI_.setString(bank);
}

void BasicAccount::set(const BasicAccount& old) { *this = old; }

void BasicAccount::set(BasicAccount&& old) { *this = std::move(old); }
