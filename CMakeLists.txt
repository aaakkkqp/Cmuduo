#最低CMAKE版本
cmake_minimum_required(VERSION 3.0)

#project（name）
project(Cmuduo)

aux_source_directory(. SOURCES)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/base
    ${PROJECT_SOURCE_DIR}/src/logger
    ${PROJECT_SOURCE_DIR}/src/http
    ${PROJECT_SOURCE_DIR}/src/net
    ${PROJECT_SOURCE_DIR}/src/memory
)
set(CXX_FLAGS
    -g
    -Wall
    -std=c++17
    )
add_library(lib src/logger/test.cpp)
add_executable(loggertest src/logger/test.cpp)
    
