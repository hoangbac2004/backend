#pragma once
#include <occi.h>

#include <type/Date.h>

#include <string>
#include <iostream>

class CitizenIdentifyCard : public oracle::occi::PObject
{
   public:
    static constexpr const char* schema = "SYSTEM";
    static constexpr const char* type_name = "CITIZEN_IDENTIFY_CARD";
    static constexpr const char* table_name = "CITIZEN_IDENTIFY_CARD_TABLE";
    static constexpr const char* primary_key = "NUMBER_";

    static oracle::occi::Environment* env;
    static void initialisation();

    long long number;
    std::string full_name;
    Date date_of_birth;
    std::string sex;
    std::string nationality;
    std::string place_of_origin;
    std::string place_of_residence;
    Date date_of_expiry;

    CitizenIdentifyCard() = default;
    ~CitizenIdentifyCard() = default;

    template <typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    CitizenIdentifyCard(long long number, T2&& full_name, T3&& date_of_birth, T4&& sex, T5&& nationality,
                        T6&& place_of_origin, T7&& place_of_residence, T8&& date_of_expiry)
        : number(number),
          full_name(std::forward<T2>(full_name)),
          date_of_birth(std::forward<T3>(date_of_birth)),
          sex(std::forward<T4>(sex)),
          nationality(std::forward<T5>(nationality)),
          place_of_origin(std::forward<T6>(place_of_origin)),
          place_of_residence(std::forward<T7>(place_of_residence)),
          date_of_expiry(std::forward<T8>(date_of_expiry))
    {
    }

    CitizenIdentifyCard(void* ctxOCCI_);
    CitizenIdentifyCard(const CitizenIdentifyCard& old);
    CitizenIdentifyCard(CitizenIdentifyCard&& old) noexcept;

    CitizenIdentifyCard& operator=(const CitizenIdentifyCard& old);
    CitizenIdentifyCard& operator=(CitizenIdentifyCard&& old) noexcept;

    void* operator new(size_t size);
    void* operator new(size_t size, const oracle::occi::Connection* sess, const OCCI_STD_NAMESPACE::string& table);
    void* operator new(size_t size, void* ctxOCCI_);
    void getSQLTypeName(oracle::occi::Environment* env, void** schemaName, unsigned int& schemaNameLen, void** typeName,
                        unsigned int& typeNameLen) const;
    virtual std::string getSQLTypeName() const;
    static void* readSQL(void* ctxOCCI_);
    virtual void readSQL(oracle::occi::AnyData& streamOCCI_) noexcept;
    static void writeSQL(void* objOCCI_, void* ctxOCCI_);
    virtual void writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept;

    void set(const CitizenIdentifyCard& old);
    void set(CitizenIdentifyCard&& old);
};
