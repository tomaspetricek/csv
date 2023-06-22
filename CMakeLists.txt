cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_COMPILER /usr/local/bin/g++-12)

project (csv)
add_subdirectory (src)

enable_testing ()
add_subdirectory (test)




