cmake_minimum_required(VERSION 4.2)
project(secure_tourism_db_system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Sql Widgets)

add_executable(secure_tourism_db_system src/main.cpp
        src/Database.cpp
        include/Database.h
        src/SearchManager.cpp
        include/SearchManager.h
        src/EncryptionManager.cpp
        include/EncryptionManager.h
        include/Record.h
        src/Controller.cpp
        include/Controller.h
        include/mainwindow.h
        src/mainwindow.cpp
        forms/MainWindow.ui
)

target_include_directories(secure_tourism_db_system PRIVATE include)

target_link_libraries(secure_tourism_db_system
        Qt6::Core
        Qt6::Sql
        Qt6::Widgets
)