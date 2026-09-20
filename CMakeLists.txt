cmake_minimum_required(VERSION 3.21)
project(spide-studio VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

add_executable(spide-studio
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    src/Editor.cpp
    src/Editor.h
    src/Explorer.cpp
    src/Explorer.h
    src/Terminal.cpp
    src/Terminal.h
    src/AIChat.cpp
    src/AIChat.h
    src/Settings.cpp
    src/Settings.h
    src/ai/IAIProvider.cpp
    src/ai/IAIProvider.h
    src/ai/SPIDEProvider.cpp
    src/ai/SPIDEProvider.h
)

target_include_directories(spide-studio PRIVATE src)
target_link_libraries(spide-studio PRIVATE Qt6::Widgets Qt6::Network)

if(WIN32)
    set_target_properties(spide-studio PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
