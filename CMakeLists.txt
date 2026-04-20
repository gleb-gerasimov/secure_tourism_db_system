cmake_minimum_required(VERSION 4.2)
project(secure_tourism_db_system)

set(CMAKE_CXX_STANDARD 20)

add_executable(secure_tourism_db_system main.cpp
        src/Client.cpp
        include/Client.h
        src/Database.cpp
        include/Database.h
        src/SearchManager.cpp
        include/SearchManager.h
        src/FileManager.cpp
        include/FileManager.h
        src/EncryptionManager.cpp
        include/EncryptionManager.h
)
