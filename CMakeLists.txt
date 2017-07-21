cmake_minimum_required(VERSION 2.8)
project (distributed_sync C CXX)

SET(CMAKE_CXX_FLAGS "-std=c++1y -Wall -fPIC")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_DEBUG   "-g -Wextra -Wno-unused-parameter -O0")

include_directories(
        ${PROJECT_SOURCE_DIR}/src
)

add_subdirectory(src)
