cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0167 NEW)


set(project_name my-project) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCE "src/*.cpp" "include/*.cpp")
file(GLOB_RECURSE HEADER "src/*.h" "src/*.hpp" "include/*.h" "include/*.hpp")

add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)

if (MSVC)
    add_compile_options(/wd4291)
endif()

##occi

include_directories($ENV{ORACLE_HOME}/sdk/include)
link_directories($ENV{ORACLE_HOME})

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/controller/MyController.cpp
        src/controller/MyController.hpp
        ${SOURCE}
        ${HEADER}
        src/exception/oracle/OracleException.cpp
        src/exception/oracle/OracleException.h
)

## link libs


find_library(ORACLE_OCCI_LIB occi HINTS $ENV{ORACLE_HOME})
find_library(ORACLE_CLNTSH_LIB clntsh HINTS $ENV{ORACLE_HOME})
find_library(ORACLE_NNZ21_LIB nnz21 HINTS $ENV{ORACLE_HOME})
find_library(ORACLE_OCIEI_LIB ociei HINTS $ENV{ORACLE_HOME})
find_library(ORACLE_OCCI_GCC occi_gcc53 HINTS $ENV{ORACLE_HOME})

message(${ORACLE_OCCI_LIB})
message(${ORACLE_CLNTSH_LIB})
message(${ORACLE_NNZ21_LIB})
message(${ORACLE_OCIEI_LIB})

find_package(oatpp 1.4.0 REQUIRED)
find_package(Boost 1.70.0 REQUIRED system filesystem locale)
find_package(ICU REQUIRED COMPONENTS uc i18n)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        PRIVATE ICU::uc ICU::i18n
        PRIVATE Boost::headers Boost::system Boost::filesystem Boost::locale
        occi_gcc53 clntsh nnz21 ociei
)

target_include_directories(${project_name}-lib PUBLIC src ${PROJECT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS} ${ICU_INCLUDE_DIRS})
## add executables

add_executable(${project_name}-exe
        src/App.cpp
       "src/data/personal information/CitizenIdentifyCard.h" "src/data/personal information/CitizenIdentifyCard.cpp" "include/tool.cpp"    "src/type/Date.h" "src/type/Date.cpp"   "include/initialisation.h" "include/initialisation.cpp" "src/entity/account/Account.h" "src/entity/account/Account.cpp"  "src/entity/client/Client.h" "src/entity/client/Client.cpp"  "src/service/client/ClientService.h"  "src/service/client/ClientService.cpp" "src/service/account/AccountService.h" "src/repository/client/ClientRepository.h" "src/repository/client/ClientRepository.cpp"  "src/repository/account/AccountRepository.h" "src/repository/account/AccountRepository.cpp" "src/service/account/AccountService.cpp" "src/repository/citizen identify card/CitizenIdentifyCardRepository.h" "src/repository/citizen identify card/CitizenIdentifyCardRepository.cpp" "src/service/citizen identify card/CitizenIdentifyCardService.h" "src/service/citizen identify card/CitizenIdentifyCardService.cpp" "include/OracleQuery.h" "include/tool.h" "src/controller/citizen identify card/CitizenIdentifyCardController.h"  "src/dto/citizen identify card/CitizenIdentifyCardDTO.h" "src/dto/ResponseDTO.hpp" "src/controller/account/AccountController.h" "src/controller/client/ClientController.h" "src/dto/client/ClientRequest.h" "src/dto/client/ClientResponse.h" "include/define.h"  "src/dto/DTOs.hpp"
        src/controller/AccountController.h
        src/exception/oracle/OracleException.cpp
        src/exception/oracle/OracleException.h
)
target_link_libraries(${project_name}-exe ${project_name}-lib)
target_link_libraries(${project_name}-exe )

add_dependencies(${project_name}-exe ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe PROPERTIES
        CXX_STANDARD 23
        CXX_EXTENSIONS ON
        CXX_STANDARD_REQUIRED ON
)

