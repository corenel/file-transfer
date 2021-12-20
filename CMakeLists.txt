cmake_minimum_required(VERSION 3.10)

project(ftrans)

# set compilation for c++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_definitions(-Wall -Wextra -Wno-unused-parameter -O2)

find_package(fmt REQUIRED)
find_package(absl REQUIRED)
find_package(AWSSDK REQUIRED COMPONENTS s3 transfer)
find_package(PkgConfig REQUIRED)
pkg_check_modules(MINIOCPP REQUIRED miniocpp)

# common include directories
include_directories(cpp/include)

# find all source files
file(GLOB_RECURSE src_files ${PROJECT_SOURCE_DIR}/cpp/src/*.cc)

# add library
add_library(${PROJECT_NAME} SHARED ${src_files})
target_link_libraries(
    ${PROJECT_NAME}
    ${MINIOCPP_LIBRARIES}
    ${AWSSDK_LINK_LIBRARIES}
    absl::time
    absl::flags
    absl::flags_parse
    fmt::fmt
    )
target_include_directories(${PROJECT_NAME} PUBLIC ${MINIOCPP_INCLUDE_DIRS})

# add executable
add_executable(example_cpp_minio ${PROJECT_SOURCE_DIR}/example/example_cpp_minio.cc)
target_link_libraries(example_cpp_minio PRIVATE ${PROJECT_NAME})