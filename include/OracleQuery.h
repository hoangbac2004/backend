#pragma once
#include <occi.h>
#include <occiControl.h>
#include <occiObjects.h>

#include <concepts>
#include <format>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>

template <typename T>
concept object_base = requires(T t, T &&other,
                               const oracle::occi::Connection *conn,
                               const std::string &tableName, void *ctxOCCI_,
                               const std::string &typeName,
                               const std::string &tableSchema,
                               const std::string &typeSchema, size_t size,
                               void *objOCCI_) {
  requires std::is_base_of_v<oracle::occi::PObject, T>;
  requires std::is_class_v<T>;

  { T::schema } -> std::convertible_to<const std::string>;
  { T::table_name } -> std::convertible_to<const std::string>;
  { T::type_name } -> std::convertible_to<const std::string>;
  { T::primary_key } -> std::convertible_to<const std::string>;
  { T::readSQL(ctxOCCI_) } -> std::same_as<void *>;
  { T::writeSQL(ctxOCCI_, objOCCI_) } -> std::same_as<void>;
  { t.set(other) } -> std::same_as<void>;
  { t.operator new(size, conn, tableName) } -> std::same_as<void *>;
};

template <typename T>
concept data_type = std::is_arithmetic_v<std::decay_t<T>> ||
    std::is_same_v<std::decay_t<T>, std::string>;

template <object_base OracleObject>
class OracleQuery {
  using Environment = oracle::occi::Environment;
  using Connection = oracle::occi::Connection;
  using Statement = oracle::occi::Statement;
  using ResultSet = oracle::occi::ResultSet;
  using SQLException = oracle::occi::SQLException;
  template <typename T>
  using Ref = oracle::occi::Ref<T>;

#define CREATE_STATEMENT_NAME(var_name, sql)                          \
  auto terminate_statement = [this](Statement *stmt) {                \
    conn->terminateStatement(stmt);                                   \
  };                                                                  \
  std::unique_ptr<Statement, decltype(terminate_statement)> var_name( \
      conn->createStatement(sql), terminate_statement);

#define CREATE_STATEMENT(sql) CREATE_STATEMENT_NAME(stmt, sql)

  template <typename T>
  std::string convert_to_string(T &&obj);

  template <typename Deleter, data_type T>
  void set_stmt(std::unique_ptr<Statement, Deleter> &stmt, long long int pos,
                const T &obj);

 public:
  Environment *env;
  Connection *conn;

 public:
  OracleQuery(Environment *env, Connection *conn);
  ~OracleQuery();
  std::vector<OracleObject> get_all();

  std::vector<OracleObject> get_more(const std::string &condition = "");

  template <data_type T>
  std::optional<OracleObject> get(T &&primary_key);

  std::optional<OracleObject> get_wtih_condition(const std::string &condition);

  void add(OracleObject &&obj_);

  template <data_type T>
  void update(T &&primary_key, OracleObject &&obj_);

  template <data_type T>
  void delete_by_primary_key(T &&primary_key);

  std::size_t execute_update(const std::string &sql);

  Ref<OracleObject> execute_query_ref(const std::string &sql);

  std::vector<Ref<OracleObject>> execute_query_ref_array(
      const std::string &sql);

  double execute_number_aggregate(const std::string &sql);

  std::string execute_string_aggregate(const std::string &sql);
};

template <object_base OracleObject>
template <typename T>
inline std::string OracleQuery<OracleObject>::convert_to_string(T &&obj) {
  std::string result;
  if constexpr (std::is_arithmetic_v<T>) {
    result = std::to_string(obj);
  } else {
    result = std::forward<T>(obj);
  }
  return result;
}

template <object_base OracleObject>
template <typename Deleter, data_type T>
inline void OracleQuery<OracleObject>::set_stmt(
    std::unique_ptr<Statement, Deleter> &stmt, long long int pos,
    const T &obj) {
  if constexpr (std::is_arithmetic_v<T>) {
    stmt->setNumber(pos, static_cast<double>(obj));
  } else if constexpr (std::same_as<std::decay<T>, std::string>) {
    stmt->setString(pos, obj);
  }
}

template <object_base OracleObject>
OracleQuery<OracleObject>::OracleQuery(Environment *env, Connection *conn)
    : env(env), conn(conn) {
  env->getMap()->put(
      std::format("{}.{}", OracleObject::schema, OracleObject::type_name),
      &OracleObject::readSQL, &OracleObject::writeSQL);
}

template <object_base OracleObject>
OracleQuery<OracleObject>::~OracleQuery() {
  env->terminateConnection(conn);
}

template <object_base OracleObject>
std::vector<OracleObject> OracleQuery<OracleObject>::get_all() {
  CREATE_STATEMENT(
      std::format("SELECT REF(X) FROM {} X", OracleObject::table_name));
  ResultSet *rs = stmt->executeQuery();
  std::vector<OracleObject> result;
  while (rs->next()) {
    result.push_back(rs->getObject(1));
  }
  return result;
}

template <object_base OracleObject>
inline std::vector<OracleObject> OracleQuery<OracleObject>::get_more(
    const std::string &condition) {
  CREATE_STATEMENT(std::format("SELECT REF(X) FROM {} X {}",
                               OracleObject::table_name, condition));
  ResultSet *rs = stmt->executeQuery();
  std::vector<OracleObject> result;
  while (rs->next()) {
    result.push_back(*static_cast<Ref<OracleObject>>(rs->getRef(1)));
  }
  return result;
}

template <object_base OracleObject>
template <data_type T>
inline std::optional<OracleObject> OracleQuery<OracleObject>::get(
    T &&primary_key) {
  std::vector<OracleObject> arr = get_more(
      std::format("WHERE {} = {}", OracleObject::primary_key, primary_key));
  return arr.empty() ? std::nullopt
                     : std::make_optional<OracleObject>(std::move(arr.front()));
}

template <object_base OracleObject>
inline std::optional<OracleObject>
OracleQuery<OracleObject>::get_wtih_condition(const std::string &condition) {
  std::vector<OracleObject> arr = get_more(condition);
  return arr.empty() ? std::nullopt
                     : std::make_optional<OracleObject>(std::move(arr.front()));
}

template <object_base OracleObject>
inline void OracleQuery<OracleObject>::add(OracleObject &&obj_) {
  try {
    new (conn, OracleObject::table_name)
        OracleObject(std::forward<OracleObject>(obj_));
    conn->commit();
  } catch (std::exception &e) {
    conn->rollback();
    throw;
  }
}

template <object_base OracleObject>
std::size_t OracleQuery<OracleObject>::execute_update(const std::string &sql) {
  CREATE_STATEMENT(sql)
  std::size_t result = 0;
  try {
    result = stmt->executeUpdate();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return result;
}

template <object_base OracleObject>
oracle::occi::Ref<OracleObject> OracleQuery<OracleObject>::execute_query_ref(
    const std::string &sql) {
  CREATE_STATEMENT(sql)
  Ref<OracleObject> result;
  try {
    ResultSet *rs = stmt->executeQuery();
    if (rs->next()) {
      result = rs->getRef(1);
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return result;
}

template <object_base OracleObject>
std::vector<oracle::occi::Ref<OracleObject>>
OracleQuery<OracleObject>::execute_query_ref_array(const std::string &sql) {
  CREATE_STATEMENT(sql)
  std::vector<Ref<OracleObject>> result;
  try {
    ResultSet *rs = stmt->executeQuery();
    while (rs->next()) {
      result.push_back(rs->getRef(1));
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return result;
}

template <object_base OracleObject>
inline double OracleQuery<OracleObject>::execute_number_aggregate(
    const std::string &sql) {
  CREATE_STATEMENT(sql);
  ResultSet *rs = stmt->executeQuery();
  rs->next();
  return rs->getNumber(1);
}

template <object_base OracleObject>
inline std::string OracleQuery<OracleObject>::execute_string_aggregate(
    const std::string &sql) {
  CREATE_STATEMENT(sql);
  ResultSet *rs = stmt->executeQuery();
  rs->next();
  return rs->getString(1);
}

template <object_base OracleObject>
template <data_type T>
inline void OracleQuery<OracleObject>::update(T &&primary_key,
                                              OracleObject &&obj_) {
  CREATE_STATEMENT(std::format("SELECT REF(X) FROM {} X WHERE {} = :1 ",
                               OracleObject::table_name,
                               OracleObject::primary_key));
  set_stmt(stmt, 1, primary_key);
  ResultSet *rs = stmt->executeQuery();
  if (rs->next()) {
    try {
      Ref<OracleObject> ref = rs->getRef(1);
      ref->markModified();  // this function is belong to
      // PObject
      ref->set(std::forward<OracleObject>(obj_));
      conn->commit();
    } catch (SQLException &e) {
      conn->rollback();
      throw;
    }
  }
}

template <object_base OracleObject>
template <data_type T>
inline void OracleQuery<OracleObject>::delete_by_primary_key(T &&primary_key) {
  CREATE_STATEMENT(std::format("DELETE FROM {} WHERE {} = :1",
                               OracleObject::table_name,
                               OracleObject::primary_key));
  stmt->setString(1, convert_to_string(primary_key));
  stmt->executeUpdate();
}