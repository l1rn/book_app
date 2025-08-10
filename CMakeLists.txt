cmake_minimum_required(VERSION 3.30)
project(book_list_app LANGUAGES C CXX)

set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/mingw_64")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(book_list_app main.cpp
        ui/mainwindow.cpp
        ui/mainwindow.h
        src/dao/author_dao.h
        src/dao/author_dao.c
        src/db/db.c
        src/db/db.h
        src/project/execute.hpp
        src/project/execute.cpp
        src/models/author.c
        src/models/book.c
        src/models/author.h
        src/models/book.h
        src/models/publisher.h
        src/models/publisher.c
        src/memory/arena.c
        src/memory/arena.h
)
add_library(
        sqlite3 STATIC third_party/sqlite/sqlite3.c
        widgets)

target_include_directories(sqlite3 PUBLIC
        third_party/sqlite
        book_list_app PUBLIC
        "src/dao/"
        "src/models/"
        "src/db"
        "src/memory"
        "src/data")


target_link_libraries(
        book_list_app
        PRIVATE
            Qt::Core Qt::Gui Qt::Widgets
            sqlite3
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
