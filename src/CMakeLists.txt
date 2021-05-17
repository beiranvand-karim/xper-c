cmake_minimum_required(VERSION 3.3)
project(xper-cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp MyWindow.cpp MyWindow.h)
add_executable(xper-cpp ${SOURCE_FILES} MyWindow.cpp MyWindow.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GTK3 REQUIRED gtkmm-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(xper-cpp ${GTK3_LIBRARIES})
