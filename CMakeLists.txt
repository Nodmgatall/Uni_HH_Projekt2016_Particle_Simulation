cmake_minimum_required(VERSION 3.0)
project(particle_simulation)

file(GLOB_RECURSE sources src/*.cpp src/*.hpp)

add_definitions(" -g -Wall -Wextra -pedantic -Werror -std=c++14 -Wno-unused-parameter")

find_package(glm REQUIRED)
find_package(Boost 1.62 REQUIRED system serialization)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(particle_simulation.x ${sources})
target_link_libraries(particle_simulation.x ${Boost_LIBRARIES})
