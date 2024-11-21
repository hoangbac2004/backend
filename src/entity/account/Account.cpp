#include "Account.h"

#include <format>
#include <iostream>

oracle::occi::Environment* Account::env = nullptr;

Account::Account(const Account& other)
    : account_number(other.account_number),
      bank(other.bank),
      name(other.name),
      alias(other.alias),
      balance(other.balance)
{
}

Account::Account(Account&& old) noexcept
    : account_number(old.account_number),
      bank(std::move(old.bank)),
      name(std::move(old.name)),
      alias(std::move(old.alias)),
      balance(old.balance)
{
}

Account& Account::operator=(const Account& other)
{
    if (this == &other)
    {
        return *this;
    }
    account_number = other.account_number;
    bank = other.bank;
    name = other.name;
    alias = other.alias;
    balance = other.balance;
    return *this;
}

Account& Account::operator=(Account&& old) noexcept
{
    if (this == &old)
    {
        return *this;
    }
    account_number = old.account_number;
    bank = std::move(old.bank);
    name = std::move(old.name);
    alias = std::move(old.alias);
    balance = old.balance;
    return *this;
}

Account::Account(void* ctxOCCI_) : oracle::occi::PObject(ctxOCCI_) {}

void Account::initialisation()
{
    extern oracle::occi::Environment* g_obj_env;
    env = g_obj_env;
}

void* Account::operator new(size_t size) { return oracle::occi::PObject::operator new(size); }

void* Account::operator new(size_t size, const oracle::occi::Connection* sess, const OCCI_STD_NAMESPACE::string& table)
{
    return oracle::occi::PObject::operator new(size, sess, table, std::format("{}.{}", schema, type_name).c_str());
}

void* Account::operator new(size_t size, void* ctxOCCI_) { return oracle::occi::PObject::operator new(size, ctxOCCI_); }

void Account::getSQLTypeName(oracle::occi::Environment* env, void** schemaName, unsigned int& schemaNameLen,
                             void** typeName, unsigned int& typeNameLen) const
{
    oracle::occi::PObject::getSQLTypeName(env, readSQL, schemaName, schemaNameLen, typeName, typeNameLen);
}

std::string Account::getSQLTypeName() const { return table_name; }

void* Account::readSQL(void* ctxOCCI_)
{
    Account* objOCCI_ = new (ctxOCCI_) Account(ctxOCCI_);
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

void Account::readSQL(oracle::occi::AnyData& streamOCCI_) noexcept
{
    account_number = std::stoll(streamOCCI_.getString());
    bank = streamOCCI_.getString();
    name = streamOCCI_.getString();
    alias = streamOCCI_.getString();
    balance = streamOCCI_.getNumber();
}

void Account::writeSQL(void* objOCCI_, void* ctxOCCI_)
{
    Account* objectOCCI_ = (Account*)objOCCI_;
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

void Account::writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept
{
    streamOCCI_.setString(std::to_string(account_number));
    streamOCCI_.setString(bank);
    streamOCCI_.setString(name);
    streamOCCI_.setString(alias);
    streamOCCI_.setNumber(balance);
}

void Account::set(const Account& old) { *this = old; }

void Account::set(Account&& old) { *this = std::move(old); }
