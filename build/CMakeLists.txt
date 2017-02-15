cmake_minimum_required(VERSION 3.0)
project(particle_simulation CXX)

set(source_dir "${CMAKE_CURRENT_SOURCE_DIR}/../src/main")
set(exec_name "particle_simulation.x")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

if (${CMAKE_EXTRA_GENERATOR} MATCHES "Eclipse CDT4")
	add_definitions (-DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE)
endif()

message(STATUS ${source_dir})

file(GLOB_RECURSE sources ../src/main/*.cpp ../src/main/*.hpp)

message(STATUS ${sources})
if(OPTIMIZED EQUAL 1)
    message("using optimized functions")
    set(exec_name "particle_sim_opti.x")
endif()
if(GPROF EQUAL 1)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    message("compiler flags for gprof set")
endif()

add_definitions(" -Wall -Wextra -Werror -W -Wshadow -Wunused-variable \
 -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers \
 -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -pedantic -pg -g ")

 include_directories(${Boost_INCLUDE_DIRS} ${source_dir})

find_package(Boost 1.62 COMPONENTS system serialization unit_test_framework)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DBOOST_AVAILABLE")
	set (CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -DBOOST_AVAILABLE")
    message(STATUS "compiling with the -DBOOST_AVAILABLE flag")
endif()

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS} -DOMP_AVAILABLE")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -DOMP_AVAILABLE")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    message(STATUS "compiling with the -DOMP_AVAILABLE flag")
endif()

add_executable(${exec_name} ${source_dir}/main.cpp ${sources})
set_target_properties(${exec_name} PROPERTIES COMPILE_FLAGS "-Ofast")

message(STATUS "CMAKE_EXE_LINKER_FLAGS: " ${CMAKE_EXE_LINKER_FLAGS})
message(STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})
message(STATUS "COMPILE_DEFINITIONS: " ${COMPILE_DEFINITIONS})
message(STATUS "COMPILE_FLAGS: " ${COMPILE_FLAGS})

if(Boost_FOUND)
	target_link_libraries(${exec_name}  ${Boost_LIBRARIES})
endif()

set(OPTIMIZED OFF CACHE BOOL "compile_optimized functions" FORCE)
set(GPROF OFF CACHE BOOL "compile with gprof support functions" FORCE)

