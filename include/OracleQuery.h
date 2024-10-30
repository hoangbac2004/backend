#include <occi.h>


#include <concepts>
#include <format>
#include <iostream>
#include <string>
#include <optional>
#include <type_traits>
#include <vector>

template <typename T>
concept object_base = requires(T t, T &&other, const oracle::occi::Connection *conn, const std::string &tableName,
                               void *ctxOCCI_, const std::string &typeName, const std::string &tableSchema,
                               const std::string &typeSchema, size_t size, void *objOCCI_) {
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
concept primary_key_type = std::is_arithmetic_v<std::decay_t<T>> || std::is_same_v<std::decay_t<T>, std::string>;

template <object_base OracleObject>
class OracleQuery {
 private:
  template <typename T>
  std::string convert_to_string(T &&obj);

 public:
  oracle::occi::Environment *env;
  oracle::occi::Connection *conn;

  OracleQuery(oracle::occi::Environment *env, oracle::occi::Connection *conn);
  ~OracleQuery();
  std::vector<OracleObject> get_all();

  std::vector<OracleObject> get_more(const std::string &condition = "");

  template <primary_key_type T>
  std::optional<OracleObject> get(T &&primary_key);

  std::optional<OracleObject> get_wtih_condition(const std::string &condition);

  void add(OracleObject &&obj_);

  template <primary_key_type T>
  void update(T &&primary_key, OracleObject &&obj_);

  template <primary_key_type T>
  void delete_by_primary_key(T &&primary_key);

  std::size_t execute_update(const std::string &sql);

  oracle::occi::Ref<OracleObject> execute_query_ref(const std::string &sql);

  std::vector<oracle::occi::Ref<OracleObject>> execute_query_ref_array(const std::string &sql);
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
OracleQuery<OracleObject>::OracleQuery(oracle::occi::Environment *env, oracle::occi::Connection *conn)
    : env(env), conn(conn) {
  env->getMap()->put(std::format("{}.{}", OracleObject::schema, OracleObject::type_name), &OracleObject::readSQL,
                     &OracleObject::writeSQL);
}

template <object_base OracleObject>
OracleQuery<OracleObject>::~OracleQuery() {
  env->terminateConnection(conn);
}

template <object_base OracleObject>
std::vector<OracleObject> OracleQuery<OracleObject>::get_all() {
  oracle::occi::Statement *stmt =
      conn->createStatement(std::format("SELECT REF(X) FROM {} X", OracleObject::table_name));
  oracle::occi::ResultSet *rs = stmt->executeQuery();
  std::vector<OracleObject> result;
  while (rs->next()) {
    result.push_back(rs->getObject(1));
  }
  conn->terminateStatement(stmt);
  return result;
}

template <object_base OracleObject>
inline std::vector<OracleObject> OracleQuery<OracleObject>::get_more(const std::string &condition) {
  oracle::occi::Statement *stmt =
      conn->createStatement(std::format("SELECT REF(X) FROM {} X {}", OracleObject::table_name, condition));
  oracle::occi::ResultSet *rs = stmt->executeQuery();
  std::vector<OracleObject> result;
  while (rs->next()) {
    result.push_back(*static_cast<oracle::occi::Ref<OracleObject>>(rs->getRef(1)));
  }
  conn->terminateStatement(stmt);
  return result;
}

template <object_base OracleObject>
template <primary_key_type T>
inline std::optional<OracleObject> OracleQuery<OracleObject>::get(T &&primary_key) {
  std::vector<OracleObject> arr = get_more(std::format("WHERE {} = {}", OracleObject::primary_key, primary_key));
  return arr.empty() ? std::nullopt : std::make_optional<OracleObject>(std::move(arr.front()));
}

template <object_base OracleObject>
inline std::optional<OracleObject> OracleQuery<OracleObject>::get_wtih_condition(const std::string &condition) {
  std::vector<OracleObject> arr = get_more(condition);
  return arr.empty() ? std::nullopt : std::make_optional<OracleObject>(std::move(arr.front()));
}

template <object_base OracleObject>
inline void OracleQuery<OracleObject>::add(OracleObject &&obj_) {
  try {
    new (conn, OracleObject::table_name) OracleObject(std::forward<OracleObject>(obj_));
    conn->commit();
  } catch (std::exception &e) {
    conn->rollback();
    throw;
  }
}

template <object_base OracleObject>
std::size_t OracleQuery<OracleObject>::execute_update(const std::string &sql) {
  oracle::occi::Statement *stmt = conn->createStatement(sql);
  std::size_t result = 0;
  try {
    result = stmt->executeUpdate();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  conn->terminateStatement(stmt);
  return result;
}

template <object_base OracleObject>
oracle::occi::Ref<OracleObject> OracleQuery<OracleObject>::execute_query_ref(const std::string &sql) {
  oracle::occi::Statement *stmt = conn->createStatement(std::string(sql));
  oracle::occi::Ref<OracleObject> result;
  try {
    oracle::occi::ResultSet *rs = stmt->executeQuery();
    if (rs->next()) {
      result = rs->getRef(1);
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  conn->terminateStatement(stmt);
  return result;
}

template <object_base OracleObject>
std::vector<oracle::occi::Ref<OracleObject>> OracleQuery<OracleObject>::execute_query_ref_array(
    const std::string &sql) {
  oracle::occi::Statement *stmt = conn->createStatement(sql);
  std::vector<oracle::occi::Ref<OracleObject>> result;
  try {
    oracle::occi::ResultSet *rs = stmt->executeQuery();
    while (rs->next()) {
      result.push_back(rs->getRef(1));
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  conn->terminateStatement(stmt);
  return result;
}

template <object_base OracleObject>
template <primary_key_type T>
inline void OracleQuery<OracleObject>::update(T &&primary_key, OracleObject &&obj_) {
  oracle::occi::Statement *stmt = conn->createStatement(
      std::format("SELECT REF(X) FROM {} X WHERE {} = :1 ", OracleObject::table_name, OracleObject::primary_key));
  stmt->setString(1, convert_to_string(primary_key));
  oracle::occi::ResultSet *rs = stmt->executeQuery();
  if (rs->next()) {
    try {
      oracle::occi::Ref<OracleObject> ref = rs->getRef(1);
      ref->markModified();  // this function is belong to
      // oracle::occi::PObject
      ref->set(std::forward<OracleObject>(obj_));
      conn->commit();
    } catch (oracle::occi::SQLException &e) {
      conn->rollback();
      conn->terminateStatement(stmt);
      throw;
    }
  }
}

template <object_base OracleObject>
template <primary_key_type T>
inline void OracleQuery<OracleObject>::delete_by_primary_key(T &&primary_key) {
  oracle::occi::Statement *stmt = conn->createStatement(
      std::format("DELETE FROM {} WHERE {} = :1", OracleObject::table_name, OracleObject::primary_key));
  stmt->setString(1, convert_to_string(primary_key));
  stmt->executeUpdate();
  conn->terminateStatement(stmt);
}