cmake_minimum_required(VERSION 3.5)
project(NGNL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_PREFIX_PATH c:/Qt/Qt5.6.0/5.6/mingw49_32/)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(EXE_NAME "ngnl")

set(EXE_SOURCES
        src/background_grid.cpp
        src/background_grid.h
        src/utils.cpp
        src/utils.h
        src/debug.cpp
        src/debug.h
        src/ngnl_main.cpp
        src/ngnl_window.h
        src/ngnl_window.cpp
        src/ngnl.ui
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(${EXE_NAME} ${EXE_SOURCES})

target_link_libraries(${EXE_NAME} Qt5::Widgets Qt5::Core)
