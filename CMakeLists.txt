cmake_minimum_required(VERSION 3.16)
project(NimNN)

set(CMAKE_CXX_STANDARD 17)

set (CMAKE_MACOSX_BUNDLE ON)
set (CMAKE_AUTOMOC ON)
set (MACOSX_BUNDLE_ICON_FILE NimNN)

if(MACOSX_BUNDLE)
    set_source_files_properties(
        ${CMAKE_SOURCE_DIR}/NimNN.icns
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources
    )
endif()

find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Widgets 
    Gui
    )

file(GLOB TS_FILES translations/*.ts)

if(WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_SOURCE_DIR}/src/icon.rc")
endif()

if(MACOSX_BUNDLE)
    target_sources(NimNN PRIVATE ${CMAKE_SOURCE_DIR}/NimNN.icns)
endif()

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

if(WIN32)
    target_sources(NimNN PRIVATE ${APP_ICON_RESOURCE_WINDOWS})
endif()

target_link_libraries(NimNN
    PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets
)
