cmake_minimum_required(VERSION 3.21)
project(SpideStudio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Core Gui Widgets)

set(SOURCES
    src/main.cpp
    src/core/CommandManager.h
    src/core/CommandManager.cpp
    src/modules/editor/CodeEditor.h
    src/modules/editor/CodeEditor.cpp
    src/modules/editor/EditorManager.h
    src/modules/editor/EditorManager.cpp
    src/modules/explorer/ExplorerWidget.h
    src/modules/explorer/ExplorerWidget.cpp
    src/modules/terminal/TerminalWidget.h
    src/modules/terminal/TerminalWidget.cpp
    src/modules/panels/OutputPanel.h
    src/modules/panels/OutputPanel.cpp
    src/modules/panels/PlaceholderPanel.h
    src/modules/panels/PlaceholderPanel.cpp
    src/ui/ActivityBar.h
    src/ui/ActivityBar.cpp
    src/ui/Sidebar.h
    src/ui/Sidebar.cpp
    src/ui/BottomPanel.h
    src/ui/BottomPanel.cpp
    src/ui/StatusBar.h
    src/ui/StatusBar.cpp
    src/ui/MainWindow.h
    src/ui/MainWindow.cpp
    resources/resources.qrc
)

add_executable(SpideStudio ${SOURCES})

target_include_directories(SpideStudio PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(SpideStudio PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
