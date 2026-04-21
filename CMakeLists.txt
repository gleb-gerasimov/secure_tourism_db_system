cmake_minimum_required(VERSION 4.2)
project(secure_tourism_db_system)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Core Sql)

add_executable(secure_tourism_db_system main.cpp
        src/Database.cpp
        include/Database.h
        src/SearchManager.cpp
        include/SearchManager.h
        src/EncryptionManager.cpp
        include/EncryptionManager.h
        src/Record.cpp
        include/Record.h
)

target_include_directories(secure_tourism_db_system PRIVATE include)

target_link_libraries(secure_tourism_db_system
        Qt6::Core
        Qt6::Sql
)