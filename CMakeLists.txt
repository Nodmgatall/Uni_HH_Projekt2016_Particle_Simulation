cmake_minimum_required(VERSION 3.0)
project(particle_simulation)

if(APPLE)
	set(CMAKE_C_COMPILER clang-omp CACHE STRING "C compiler" FORCE)
	set(CMAKE_CXX_COMPILER clang-omp++ CACHE STRING "C++ compiler" FORCE)
endif()

file(GLOB_RECURSE sources src/*.cpp src/*.hpp)

add_definitions(" -g -Wall -Wextra -pedantic -Werror -std=c++14 -Wno-unused-parameter -fassociative-math -ftree-vectorize -Ofast ")

find_package(Boost 1.62 COMPONENTS system serialization)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DBOOST")
endif()

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(particle_simulation.x ${sources})
if(Boost_FOUND)
	target_link_libraries(particle_simulation.x ${Boost_LIBRARIES})
endif()