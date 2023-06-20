cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 23)
project(csv)
add_executable(csv main.cpp)
include_directories(../include)
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(csv PUBLIC ${Boost_LIBRARIES})
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -march=native")




