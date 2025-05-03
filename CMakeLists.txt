cmake_minimum_required(VERSION 3.16)
project(MessengerAdmin)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)
qt_standard_project_setup()

add_executable(MessengerAdmin
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    dbmanager.cpp
    dbmanager.h
)

target_link_libraries(MessengerAdmin PRIVATE Qt6::Widgets Qt6::Sql)
