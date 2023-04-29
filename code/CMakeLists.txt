cmake_minimum_required(VERSION 3.0.0)
project(ARCH_project VERSION 0.1.0)

include(CTest)
enable_testing()

set(SOURCE Camera.cpp main.cpp robotCommands.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Mosquitto IMPORTED_TARGET libmosquitto REQUIRED)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

add_executable(ARCH_project ${SOURCE})

target_link_libraries(ARCH_project ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} PkgConfig::Mosquitto)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
