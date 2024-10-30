#include "Transaction.h"

#include <format>
#include <iostream>
#include <oatpp/Types.hpp>

oracle::occi::Environment* Transaction::env = nullptr;

Transaction::Transaction(const Transaction& other)
    : from(other.from), to(other.to), amount(other.amount), message(other.message), state(other.state) {}

Transaction::Transaction(Transaction&& old) noexcept
    : from(std::move(old.from)),
      to(std::move(old.to)),
      amount(old.amount),
      message(std::move(old.message)),
      state(old.state) {}

Transaction& Transaction::operator=(const Transaction& other) {
  if (this == &other) {
    return *this;
  }
  from = other.from;
  to = other.to;
  amount = other.amount;
  message = other.message;
  state = other.state;
  return *this;
}

Transaction& Transaction::operator=(Transaction&& old) noexcept {
  if (this == &old) {
    return *this;
  }
  from = std::move(old.from);
  to = std::move(old.to);
  amount = old.amount;
  message = std::move(old.message);
  state = old.state;
  return *this;
}

Transaction::Transaction(void* ctxOCCI_) : oracle::occi::PObject(ctxOCCI_) {}

void Transaction::initialisation() {
  extern oracle::occi::Environment* g_obj_env;
  env = g_obj_env;
  env->getMap()->put(std::format("{}.{}", schema, type_name).c_str(), readSQL, writeSQL);
}

void* Transaction::operator new(size_t size) { return oracle::occi::PObject::operator new(size); }

void* Transaction::operator new(size_t size, const oracle::occi::Connection* sess,
                                const OCCI_STD_NAMESPACE::string& table) {
  return oracle::occi::PObject::operator new(size, sess, table, std::format("{}.{}", schema, type_name).c_str());
}

void* Transaction::operator new(size_t size, void* ctxOCCI_) {
  return oracle::occi::PObject::operator new(size, ctxOCCI_);
}

void Transaction::getSQLTypeName(oracle::occi::Environment* env, void** schemaName, unsigned int& schemaNameLen,
                                 void** typeName, unsigned int& typeNameLen) const {
  oracle::occi::PObject::getSQLTypeName(env, readSQL, schemaName, schemaNameLen, typeName, typeNameLen);
}

std::string Transaction::getSQLTypeName() const { return table_name; }

void* Transaction::readSQL(void* ctxOCCI_) {
  Transaction* objOCCI_ = new (ctxOCCI_) Transaction(ctxOCCI_);
  oracle::occi::AnyData streamOCCI_(ctxOCCI_);
  try {
    if (streamOCCI_.isNull()) {
      objOCCI_->setNull();
    } else {
      objOCCI_->readSQL(streamOCCI_);
    }
  } catch (oracle::occi::SQLException& e) {
    delete objOCCI_;
    e.setErrorCtx(ctxOCCI_);
    std::cerr << e.what() << std::endl;
    return (void*)nullptr;
  }
  return (void*)objOCCI_;
}

void Transaction::readSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  from = *static_cast<BasicAccount*>(streamOCCI_.getObject(&BasicAccount::readSQL));
  to = *static_cast<BasicAccount*>(streamOCCI_.getObject(&BasicAccount::readSQL));
  amount = streamOCCI_.getNumber();
  message = streamOCCI_.getString();
  state = streamOCCI_.getNumber();
}

void Transaction::writeSQL(void* objOCCI_, void* ctxOCCI_) {
  Transaction* objectOCCI_ = (Transaction*)objOCCI_;
  oracle::occi::AnyData streamOCCI_(ctxOCCI_);
  try {
    if (objectOCCI_->isNull()) {
      streamOCCI_.setNull();
    } else {
      objectOCCI_->writeSQL(streamOCCI_);
    }
  } catch (oracle::occi::SQLException& e) {
    e.setErrorCtx(ctxOCCI_);
    std::cerr << e.what() << std::endl;
  }
}

void Transaction::writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  streamOCCI_.setObject(&from);
  streamOCCI_.setObject(&to);
  streamOCCI_.setNumber(amount);
  streamOCCI_.setString(message);
  streamOCCI_.setNumber(state);
}

void Transaction::set(const Transaction& old) { *this = old; }

void Transaction::set(Transaction&& old) { *this = std::move(old); }