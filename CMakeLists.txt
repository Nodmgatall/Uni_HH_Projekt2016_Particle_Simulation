cmake_minimum_required(VERSION 3.0)
project(particle_simulation)

file(GLOB_RECURSE sources src/*.cpp src/*.hpp)

add_definitions(" -g -Wall -Wextra -pedantic -Werror -std=c++11 -Wno-unused-parameter")

find_package(glm REQUIRED)

add_executable(particle_simulation ${sources})

