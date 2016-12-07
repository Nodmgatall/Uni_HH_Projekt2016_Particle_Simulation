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

add_definitions("-Wall -Wextra -Werror -Wno-unused-parameter -pedantic -g")
add_definitions("-fassociative-math -Ofast")


find_package(Boost 1.62 COMPONENTS system serialization unit_test_framework)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DBOOST")
	message("compiling with the -DBOOST flag")
endif()

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(particle_simulation.x src/main/main.cpp ${sources})
SET_TARGET_PROPERTIES(particle_simulation.x PROPERTIES COMPILE_FLAGS "-fassociative-math -Ofast")

if(Boost_FOUND)
	target_link_libraries(particle_simulation.x ${Boost_LIBRARIES})
endif()

if(Boost_FOUND)
	enable_testing ()
	add_definitions("-I${CMAKE_SOURCE_DIR}/src/main")
	add_library(particle_simulation_test_lib STATIC ${sources} )
	set_target_properties(particle_simulation_test_lib PROPERTIES COMPILE_FLAGS "-O0 -ggdb")
	set_target_properties(particle_simulation_test_lib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Testing/Binary)
	set(ENV{CTEST_OUTPUT_ON_FAILURE} TRUE)
	file(GLOB_RECURSE test_sources src/test*.cpp)
	foreach(testSrc ${test_sources})	        
		get_filename_component(testName ${testSrc} NAME_WE)
        add_executable(${testName}.x ${testSrc})
        target_link_libraries(${testName}.x ${Boost_LIBRARIES} particle_simulation_test_lib)
        set_target_properties(${testName}.x PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Testing/Binary)
        add_test(NAME ${testName}.x 
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Testing/Binary 
                 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/Testing/Binary/${testName}.x)
	endforeach()
	add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
endif()