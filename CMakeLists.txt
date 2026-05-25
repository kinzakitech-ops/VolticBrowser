cmake_minimum_required(VERSION 3.20)
project(VolticBrowser VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets WebEngineWidgets)
add_executable(VolticBrowser
    main.cpp
    core/FileManager.cpp
    core/AccountManager.cpp
    core/HistoryLogger.cpp
    ui/RegisterWindow.cpp
    ui/CongratsWindow.cpp
    ui/WarningWindow.cpp
    ui/LoginWindow.cpp
    ui/MainWindow.cpp
    ui/SettingsSidebar.cpp
    ui/DownloadCenter.cpp
)
target_link_libraries(VolticBrowser Qt6::Core Qt6::Widgets Qt6::WebEngineWidgets)
if(WIN32)
    set_target_properties(VolticBrowser PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
