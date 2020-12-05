cmake_minimum_required(VERSION 3.1)
project(Tablebses VERSION 1.0)

find_package(GTest REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(check_position src/main.cpp)

target_include_directories(check_position PRIVATE include)
target_link_libraries(check_position Boost::program_options)
