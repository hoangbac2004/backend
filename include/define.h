#pragma once

#define CUSTOM_DEFAULT_QUERY(query)               \
  try {                                           \
    query;                                        \
    return std::string{};                                    \
  } catch (const oracle::occi::SQLException& e) { \
    return e.what();                              \
  }
