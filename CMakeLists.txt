cmake_minimum_required(VERSION 3.21)
project(SpideStudio LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)
qt_add_executable(SpideStudio
 src/main.cpp src/MainWindow.h src/MainWindow.cpp
 src/Editor.h src/Editor.cpp src/Explorer.h src/Explorer.cpp
 src/AIChat.h src/AIChat.cpp src/Terminal.h src/Terminal.cpp)
target_link_libraries(SpideStudio PRIVATE Qt6::Widgets Qt6::Network)
