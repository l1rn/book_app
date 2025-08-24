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

if(BUILD_WITH_ASAN)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif ()

include_directories(
        src/
        third_party/hash
        third_party/sqlite
)

## Third party lib
add_library(sqlite3 STATIC third_party/sqlite/sqlite3.c)
target_include_directories(sqlite3 PUBLIC third_party/sqlite)
set_target_properties(sqlite3 PROPERTIES FOLDER "ThirdParty")

## Core components lib
add_library(app_core STATIC
        third_party/hash/uthash.h
        src/core/dao/author_dao.h
        src/core/dao/author_dao.c
        src/core/db/db.c
        src/core/db/db.h
        src/project/ApplicationManager.hpp
        src/project/ApplicationManager.cpp
        src/core/models/author.c
        src/core/models/book.c
        src/core/models/author.h
        src/core/models/book.h
        src/core/models/publisher.h
        src/core/models/publisher.c
        src/core/memory/arena_api.c
        src/core/memory/arena_api.h
        src/services/ArenaGuard.cpp
        src/services/ArenaGuard.hpp
        src/services/AuthorService.cpp
        src/services/AuthorService.hpp
)

target_include_directories(app_core PUBLIC
    src/
    "src/core/memory/"
    "src/core/models/"
    "src/core/db/"
    "src/core/dao/"
    "src/project"
    "src/services"
    "ui/"
    "third_party"
)

target_link_libraries(app_core PRIVATE sqlite3)
set_target_properties(app_core PROPERTIES FOLDER "Libraries")

## UI components lib
add_library(app_ui STATIC
    ui/main_window.cpp
    ui/main_window.hpp
)

target_include_directories(app_ui PUBLIC ui/)
target_link_libraries(app_ui PRIVATE Qt6::Widgets app_core)
set_target_properties(app_ui PROPERTIES FOLDER "Libraries")

# Main executable
add_executable(book_list_app main.cpp)
target_link_libraries(book_list_app PRIVATE app_ui Qt6::Widgets)
set_target_properties(book_list_app PROPERTIES FOLDER "Applications")

install(TARGETS book_list_app
        RUNTIME DESTINATION bin
        BUNDLE DESTINATION .)

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