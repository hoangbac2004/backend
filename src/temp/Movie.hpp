#pragma once

#include <occi.h>

#include <utility>

#include "type/Date.h"

class Movie : public oracle::occi::PObject {
 public:
  static constexpr const char* schema = "SYSTEM";
  static constexpr const char* type_name = "MOVIE";
  static constexpr const char* table_name = "MOVIE_TABLE";
  static constexpr const char* primary_key = "ID";

  static oracle::occi::Environment* env;

 public:
  int id;
  std::string title;
  Date release_date;
  double rating;
  int duration;
  std::string description;

 public:
  Movie() = default;
  ~Movie() = default;

  Movie(const Movie&) = default;
  Movie(Movie&&) = default;
  Movie& operator=(const Movie&) = default;
  Movie& operator=(Movie&&) = default;
  template <typename T1, typename T2, typename T3>
  Movie(int id, T1&& title, T2&& release_date, double rating, int duration,
        T3&& description)
      : id(id),
        title(std::forward<T1>(title)),
        release_date(std::forward<T2>(release_date)),
        rating(rating),
        duration(duration),
        description(std::forward<T3>(description)) {}

  Movie(void* ctxOCCI_);
  static void initialisation();
  void* operator new(size_t size);
  void* operator new(size_t size, const oracle::occi::Connection* sess,
                     const OCCI_STD_NAMESPACE::string& table);
  void* operator new(size_t size, void* ctxOCCI_);
  void getSQLTypeName(oracle::occi::Environment* env, void** schemaName,
                      unsigned int& schemaNameLen, void** typeName,
                      unsigned int& typeNameLen) const;
  virtual std::string getSQLTypeName() const;
  static void* readSQL(void* ctxOCCI_);
  virtual void readSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;
  static void writeSQL(void* objOCCI_, void* ctxOCCI_);
  virtual void writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;

  void set(const Movie& old);
  void set(Movie&& old);
};