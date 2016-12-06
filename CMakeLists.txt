cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (${CMAKE_EXTRA_GENERATOR} MATCHES "Eclipse CDT4")
	add_definitions (-DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE)
endif()

project(particle_simulation CXX)

if(APPLE)
	set(CMAKE_C_COMPILER clang-omp CACHE STRING "C compiler" FORCE)
	set(CMAKE_CXX_COMPILER clang-omp++ CACHE STRING "C++ compiler" FORCE)
endif()

file(GLOB_RECURSE sources src/main/*.cpp src/main/*.hpp)
file(GLOB_RECURSE test_sources src/*.cpp src/*.hpp)
list(REMOVE_ITEM test_sources "${CMAKE_SOURCE_DIR}/src/main/main.cpp")

add_definitions("-Wall -Wextra -Werror -Wno-unused-parameter -pedantic -g")
add_definitions("-fassociative-math -Ofast")
add_definitions("-I${CMAKE_SOURCE_DIR}/src/main")

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

add_executable(particle_simulation.x src/main/main.cpp ${sources})

enable_testing ()

add_executable (particle_simulation_test.x src/test/main.cpp ${test_sources})

add_test (particle_simulation_test.x ${EXECUTABLE_OUTPUT_PATH}/particle_simulation_test.x)
if(Boost_FOUND)
	target_link_libraries(particle_simulation.x ${Boost_LIBRARIES})
	target_link_libraries(particle_simulation_test.x ${Boost_LIBRARIES})
endif()
