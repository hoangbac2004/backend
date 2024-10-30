#include "CitizenIdentifyCard.h"

#include <format>
#include <iostream>

oracle::occi::Environment* CitizenIdentifyCard::env = nullptr;

void CitizenIdentifyCard::initialisation() {
  extern oracle::occi::Environment* g_obj_env;
  env = g_obj_env;
  env->getMap()->put(std::format("{}.{}", schema, type_name).c_str(), &readSQL, &writeSQL);
}

CitizenIdentifyCard::CitizenIdentifyCard(const CitizenIdentifyCard& old)
    : number(old.number),
      full_name(old.full_name),
      date_of_birth(old.date_of_birth),
      sex(old.sex),
      nationality(old.nationality),
      place_of_origin(old.place_of_origin),
      place_of_residence(old.place_of_residence),
      date_of_expiry(old.date_of_expiry) {}

CitizenIdentifyCard::CitizenIdentifyCard(CitizenIdentifyCard&& old) noexcept
    : number(old.number),
      full_name(std::move(old.full_name)),
      date_of_birth(std::move(old.date_of_birth)),
      sex(std::move(old.sex)),
      nationality(std::move(old.nationality)),
      place_of_origin(std::move(old.place_of_origin)),
      place_of_residence(std::move(old.place_of_residence)),
      date_of_expiry(std::move(old.date_of_expiry)) {}

CitizenIdentifyCard& CitizenIdentifyCard::operator=(const CitizenIdentifyCard& old) {
  if (this == &old) {
    return *this;
  }
  number = old.number;
  full_name = old.full_name;
  date_of_birth = old.date_of_birth;
  sex = old.sex;
  nationality = old.nationality;
  place_of_origin = old.place_of_origin;
  place_of_residence = old.place_of_residence;
  date_of_expiry = old.date_of_expiry;
  return *this;
}

CitizenIdentifyCard& CitizenIdentifyCard::operator=(CitizenIdentifyCard&& old) noexcept {
  if (this == &old) {
    return *this;
  }
  number = old.number;
  full_name = std::move(old.full_name);
  date_of_birth = std::move(old.date_of_birth);
  sex = std::move(old.sex);
  nationality = std::move(old.nationality);
  place_of_origin = std::move(old.place_of_origin);
  place_of_residence = std::move(old.place_of_residence);
  date_of_expiry = std::move(old.date_of_expiry);
  return *this;
}

CitizenIdentifyCard::CitizenIdentifyCard(void* ctxOCCI_) : oracle::occi::PObject(ctxOCCI_) {}

void* CitizenIdentifyCard::operator new(size_t size) { return oracle::occi::PObject::operator new(size); }

void* CitizenIdentifyCard::operator new(size_t size, const oracle::occi::Connection* sess,
                                        const OCCI_STD_NAMESPACE::string& table) {
  return oracle::occi::PObject::operator new(size, sess, table, std::format("{}.{}", schema, type_name).c_str());
}

void* CitizenIdentifyCard::operator new(size_t size, void* ctxOCCI_) {
  return oracle::occi::PObject::operator new(size, ctxOCCI_);
}

void CitizenIdentifyCard::getSQLTypeName(oracle::occi::Environment* env, void** schemaName, unsigned int& schemaNameLen,
                                         void** typeName, unsigned int& typeNameLen) const {
  return oracle::occi::PObject::getSQLTypeName(env, &CitizenIdentifyCard::readSQL, schemaName, schemaNameLen, typeName,
                                               typeNameLen);
}

std::string CitizenIdentifyCard::getSQLTypeName() const { return table_name; }

void* CitizenIdentifyCard::readSQL(void* ctxOCCI_) {
  CitizenIdentifyCard* objOCCI_ = new (ctxOCCI_) CitizenIdentifyCard(ctxOCCI_);
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

void CitizenIdentifyCard::readSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  number = static_cast<long long>((double)streamOCCI_.getNumber());
  full_name = streamOCCI_.getString();
  date_of_birth = Date(streamOCCI_.getDate());
  sex = streamOCCI_.getString();
  nationality = streamOCCI_.getString();
  place_of_origin = streamOCCI_.getString();
  place_of_residence = streamOCCI_.getString();
  date_of_expiry = Date(streamOCCI_.getDate());
}

void CitizenIdentifyCard::writeSQL(void* objOCCI_, void* ctxOCCI_) {
  CitizenIdentifyCard* objectOCCI_ = (CitizenIdentifyCard*)objOCCI_;
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

void CitizenIdentifyCard::writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  streamOCCI_.setNumber(static_cast<double>(number));
  streamOCCI_.setString(full_name);
  streamOCCI_.setDate(date_of_birth.to_oracle_date(env));
  streamOCCI_.setString(sex);
  streamOCCI_.setString(nationality);
  streamOCCI_.setString(place_of_origin);
  streamOCCI_.setString(place_of_residence);
  streamOCCI_.setDate(date_of_expiry.to_oracle_date(env));
}

void CitizenIdentifyCard::set(const CitizenIdentifyCard& old) { *this = old; }

void CitizenIdentifyCard::set(CitizenIdentifyCard&& old) { *this = std::move(old); }
