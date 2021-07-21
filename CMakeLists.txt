cmake_minimum_required(VERSION 3.16)
project(xper-cpp)


set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")
set(SOURCE_FILES
        src/main.cpp
        src/window/MyWindow.cpp
        src/appContainer/AppContainer.cpp
        src/drawer/Drawer.cpp
        src/drawer/DrawOptions.cpp)

add_executable(xper-cpp ${SOURCE_FILES})


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtkmm-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/resource)

link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(xper-cpp ${GTK3_LIBRARIES})

file(COPY resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY resource DESTINATION ${CMAKE_BINARY_DIR})
file(COPY style DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ui DESTINATION  ${CMAKE_BINARY_DIR})

### install the project
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

install(TARGETS xper-cpp DESTINATION xper-cpp)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION xper-cpp)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/style DESTINATION xper-cpp)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/resource DESTINATION xper-cpp)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/ui DESTINATION xper-cpp)

