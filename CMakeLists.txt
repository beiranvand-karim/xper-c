cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

project(xper-cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE_FILES
        src/main.cpp
        src/ui/MainWindow.cpp
        src/ui/AppContainer.cpp
        src/ui/StartingBox.cpp
        src/ui/SidebarDrawing.cpp
        src/ui/CanvasContainer.cpp
        src/ui/MainCanvas.cpp
        src/drawingItems/RectItem.cpp
        )

add_executable(xper-cpp ${SOURCE_FILES})



find_package(PkgConfig REQUIRED)

### Gtkmm dependency
pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)
include_directories(${GTKMM3_INCLUDE_DIRS})
target_link_libraries(xper-cpp ${GTKMM3_LIBRARIES})

### GOOCANVASMM dependency
pkg_check_modules(GOOCANVAS REQUIRED goocanvasmm-2.0)
include_directories(${GOOCANVAS_INCLUDE_DIRS})
target_link_libraries(xper-cpp ${GOOCANVAS_LIBRARIES})

### resource
file(COPY resource/glade DESTINATION ${CMAKE_BINARY_DIR})
file(COPY resource DESTINATION ${CMAKE_BINARY_DIR})
file(COPY style DESTINATION ${CMAKE_BINARY_DIR})


### install the project
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

install(TARGETS xper-cpp DESTINATION xper-cpp)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION xper-cpp)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/style DESTINATION xper-cpp)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/resource DESTINATION xper-cpp)
install(DIRECTORY resource/glade DESTINATION xper-cpp)
