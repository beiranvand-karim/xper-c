cmake_minimum_required(VERSION 3.3)
project(xper-cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

set(SOURCE_FILES main.cpp window/MyWindow.cpp window/MyWindow.h sidebar/SidebarContainer.cpp sidebar/SidebarContainer.h textview/TextViewContainer.cpp textview/TextViewContainer.h)
add_executable(xper-cpp ${SOURCE_FILES} window/MyWindow.cpp window/MyWindow.h sidebar/SidebarContainer.cpp sidebar/SidebarContainer.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtkmm-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(xper-cpp ${GTK3_LIBRARIES})
