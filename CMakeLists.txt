cmake_minimum_required(VERSION 3.20)
project(book_list_app LANGUAGES C CXX)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/mingw_64")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# -------- core files --------
file(GLOB_RECURSE APP_CORE_SOURCES_C
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)
file(GLOB_RECURSE APP_CORE_SOURCES_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
)

file(GLOB_RECURSE APP_CORE_SOURCES_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

set(APP_CORE_SOURCES
    ${APP_CORE_SOURCES_C}
    ${APP_CORE_SOURCES_CPP}
    ${APP_CORE_SOURCES_HEADERS}
)

# ------------- Third-party: sqlite (static) -------------
add_library(sqlite3 STATIC third_party/sqlite/sqlite3.c)

target_include_directories(sqlite3
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/sqlite>
            $<INSTALL_INTERFACE:include/third_party/sqlite>
)

target_sources(sqlite3
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sqlite/sqlite3.h
)

set_target_properties(sqlite3 PROPERTIES FOLDER "ThirdParty")


# ------------ app_core library ----------------
add_library(app_core STATIC)
target_sources(app_core
    PRIVATE
        ${APP_CORE_SOURCES}
)

target_include_directories(app_core
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
            $<INSTALL_INTERFACE:include>
)

target_link_libraries(app_core PUBLIC sqlite3)
set_target_properties(app_core PROPERTIES FOLDER "Libraries")

## ----------- app_ui library ----------------
add_library(app_ui STATIC
        ui/MainWindow.cpp
        ui/MainWindow.hpp
)

target_include_directories(app_ui
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ui>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
            $<INSTALL_INTERFACE:include>
)

target_link_libraries(app_ui PRIVATE Qt6::Widgets Qt6::Gui app_core)
set_target_properties(app_ui PROPERTIES FOLDER "Libraries")

# ----------- Main executable --------------
add_executable(book_list_app
        main.cpp
        resources.qrc
)

target_link_libraries(book_list_app
        PRIVATE
            app_core
            app_ui
            Qt6::Widgets
            Qt6::Gui
)

target_include_directories(book_list_app
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)
add_library(SQLite3::SQLite3 ALIAS sqlite3)

set_target_properties(book_list_app PROPERTIES FOLDER "Applications")

install(TARGETS book_list_app
        RUNTIME DESTINATION bin
        BUNDLE DESTINATION .)

install(
        FILES "${CMAKE_CURRENT_SOURCE_DIR}/third_party/sqlite/sqlite3.h"
        DESTINATION include/third_party/sqlite
)

if(WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if(MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif()

    find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
    get_target_property(QtCore_location Qt6::Core LOCATION)
    get_filename_component(QT_INSTALL_PATH "${QtCore_location}" DIRECTORY)
    get_filename_component(QT_INSTALL_PATH "${QT_INSTALL_PATH}" DIRECTORY)

    if(EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET book_list_app POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:book_list_app>/plugins/platforms/"
        )
        add_custom_command(TARGET book_list_app POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:book_list_app>/plugins/platforms/"
        )
    endif()

    foreach(QT_LIB Core Gui Widgets)
        add_custom_command(TARGET book_list_app POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:book_list_app>"
        )
    endforeach()
endif()