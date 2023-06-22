include_directories(../include)
add_executable(csv main.cpp)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(csv PUBLIC ${Boost_LIBRARIES})

add_definitions(-DNDEBUG)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -march=native")