#include "Movie.hpp"

#include <format>
#include <iostream>

oracle::occi::Environment* Movie::env;

Movie::Movie(void* ctxOCCI_) : oracle::occi::PObject(ctxOCCI_) {}

void Movie::initialisation() {
  extern oracle::occi::Environment* g_obj_env;
  env = g_obj_env;
}

void* Movie::operator new(size_t size) {
  return oracle::occi::PObject::operator new(size);
}

void* Movie::operator new(size_t size, const oracle::occi::Connection* sess,
                          const OCCI_STD_NAMESPACE::string& table) {
  return oracle::occi::PObject::operator new(
      size, sess, table, std::format("{}.{}", schema, type_name).c_str());
}

void* Movie::operator new(size_t size, void* ctxOCCI_) {
  return oracle::occi::PObject::operator new(size, ctxOCCI_);
}

void Movie::getSQLTypeName(oracle::occi::Environment* env, void** schemaName,
                           unsigned int& schemaNameLen, void** typeName,
                           unsigned int& typeNameLen) const {
  oracle::occi::PObject::getSQLTypeName(env, readSQL, schemaName, schemaNameLen,
                                        typeName, typeNameLen);
}

std::string Movie::getSQLTypeName() const { return table_name; }

void* Movie::readSQL(void* ctxOCCI_) {
  Movie* objOCCI_ = new (ctxOCCI_) Movie(ctxOCCI_);
  oracle::occi::AnyData streamOCCI_(ctxOCCI_);
  try {
    if (streamOCCI_.isNull()) {
      objOCCI_->setNull();
    } else {
      objOCCI_->readSQL(streamOCCI_);
    }
  } catch (oracle::occi::SQLException& e) {
    delete objOCCI_;
    std::cerr << e.what() << std::endl;
    return (void*)nullptr;
  }
  return (void*)objOCCI_;
}

void Movie::readSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  id = streamOCCI_.getNumber();
  title = streamOCCI_.getString();
  release_date = streamOCCI_.getDate();
  rating = streamOCCI_.getNumber();
  duration = streamOCCI_.getNumber();
  description = streamOCCI_.getString();
}
void Movie::writeSQL(void* objOCCI_, void* ctxOCCI_) {
  Movie* objectOCCI_ = (Movie*)objOCCI_;
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

void Movie::writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  streamOCCI_.setNumber(id);
  streamOCCI_.setString(title);
  streamOCCI_.setDate(release_date.to_oracle_date(env));
  streamOCCI_.setNumber(rating);
  streamOCCI_.setNumber(duration);
  streamOCCI_.setString(description);
}

void Movie::set(const Movie& old) { *this = old; }

void Movie::set(Movie&& old) { *this = std::move(old); }
