cmake_minimum_required(VERSION 3.16)
project(NimNN)

set(CMAKE_CXX_STANDARD 17)

set (CMAKE_MACOSX_BUNDLE ON)
set (CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Widgets 
    Gui
    )

file(GLOB TS_FILES translations/*.ts)
# qt_add_translations(NimNN TS_FILES ${TS_FILES})

add_executable(NimNN 
    MACOSX_BUNDLE
    WIN32
    src/main.cpp
    src/gamewindow.cpp
    src/trainwindow.cpp
    src/game.cpp
    src/nn.cpp
    src/train.cpp
    src/utils.cpp
    src/sampling.cpp
    headers/gamewindow.h
    headers/trainwindow.h
    # headers/game.h
    # headers/nn.h
    # headers/train.h
    # headers/utils.h
    )

target_link_libraries(NimNN
    PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets
)
