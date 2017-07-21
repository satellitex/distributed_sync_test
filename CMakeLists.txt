cmake_minimum_required(VERSION 2.8)
project (distributed_sync C CXX)

SET(CMAKE_CXX_FLAGS "-std=c++1y -Wall -fPIC")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_DEBUG   "-g -Wextra -Wno-unused-parameter -O0")
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)


include_directories(
        ${PROJECT_SOURCE_DIR}/src
)

include(cmake/dependencies.cmake)

add_subdirectory(src)
