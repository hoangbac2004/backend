#include "Client.h"

#include <format>
#include <iostream>

//service

#include <service/citizen identify card/CitizenIdentifyCardService.h>

oracle::occi::Environment* Client::env = nullptr;

Client::Client(const Client& other)
    : CIC(other.CIC), username(other.username), password(other.password) {}

Client::Client(Client&& old) noexcept
    : CIC(std::move(old.CIC)),
      username(std::move(old.username)),
      password(std::move(old.password)) {}

Client& Client::operator=(const Client& other) {
    if (this == &other) {
        return *this;
    }
    CIC = other.CIC;
    username = other.username;
    password = other.password;
    return *this;
}

Client& Client::operator=(Client&& other) noexcept{
    if (this == &other) {
        return *this;
    }
    CIC = std::move(other.CIC);
    username = std::move(other.username);
    password = std::move(other.password);
    return *this;
}
Client::Client(void* ctxOCCI_) : oracle::occi::PObject(ctxOCCI_) {}

void Client::initialisation() {
    extern oracle::occi::Environment* g_obj_env;
    env = g_obj_env;
    env->getMap()->put(std::format("{}.{}", schema, type_name).c_str(), readSQL,
                       writeSQL);
}

void* Client::operator new(size_t size) {
    return oracle::occi::PObject::operator new(size);
}

void* Client::operator new(size_t size, const oracle::occi::Connection* sess,
                           const OCCI_STD_NAMESPACE::string& table) {
    return oracle::occi::PObject::operator new(
        size, sess, table, std::format("{}.{}", schema, type_name).c_str());
}

void* Client::operator new(size_t size, void* ctxOCCI_) {
    return oracle::occi::PObject::operator new(size, ctxOCCI_);
}

void Client::getSQLTypeName(oracle::occi::Environment* env, void** schemaName,
                            unsigned int& schemaNameLen, void** typeName,
                            unsigned int& typeNameLen) const {
    oracle::occi::PObject::getSQLTypeName(env, readSQL, schemaName,
                                          schemaNameLen, typeName, typeNameLen);
}

std::string Client::getSQLTypeName() const { return table_name; }

void* Client::readSQL(void* ctxOCCI_) {
    Client* objOCCI_ = new (ctxOCCI_) Client(ctxOCCI_);
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

void Client::readSQL(oracle::occi::AnyData& streamOCCI_) noexcept{
    CIC = std::move(service::CitizenIdentifyCardService::get((double)streamOCCI_.getNumber())).value();
    username = streamOCCI_.getString();
    password = streamOCCI_.getString();
}

void Client::writeSQL(void* objOCCI_, void* ctxOCCI_) {
    Client* objectOCCI_ = (Client*)objOCCI_;
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

void Client::writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
    streamOCCI_.setNumber(static_cast<double>(CIC.number));
    streamOCCI_.setString(username);
    streamOCCI_.setString(password);
}

void Client::set(const Client& old) { *this = old; }

void Client::set(Client&& old) { *this = std::move(old); }
