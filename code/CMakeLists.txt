cmake_minimum_required(VERSION 3.0.0)
project(ARCH_project VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${OpenCV_INCLUDE_DIRS})
find_package(OpenCV REQUIRED)

add_executable(ARCH_project Camera.cpp)

target_link_libraries(ARCH_project ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
