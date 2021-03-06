cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (${CMAKE_EXTRA_GENERATOR} MATCHES "Eclipse CDT4")
	add_definitions (-DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE)
endif()

project(particle_simulation CXX)

file(GLOB_RECURSE sources src/main/*.cpp src/main/*.hpp)

add_definitions("-Wall -Wextra -Werror -W -Wshadow -Wunused-variable \
 -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers \
 -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -pedantic")

include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src/main)

find_package(Boost 1.62 COMPONENTS system serialization unit_test_framework)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DBOOST_AVAILABLE")
	set (CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -DBOOST_AVAILABLE")
	message("compiling with the -DBOOST_AVAILABLE flag")
endif()

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS} -DOMP_AVAILABLE")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -DOMP_AVAILABLE")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
	message("compiling with the -DOMP_AVAILABLE flag")
endif()

add_executable(particle_simulation.x src/main/main.cpp ${sources})
set_target_properties(particle_simulation.x PROPERTIES COMPILE_FLAGS " -Ofast -fassociative-math -funit-at-a-time -funswitch-loops -fprefetch-loop-arrays -fmerge-all-constants -march=native ")

add_executable(particle_simulation_vectorized.x src/main/main.cpp ${sources})
set_target_properties(particle_simulation_vectorized.x PROPERTIES COMPILE_FLAGS " -Ofast -DOPTIMIZED=1 -fassociative-math -funit-at-a-time -funswitch-loops -fprefetch-loop-arrays -fmerge-all-constants -march=native")
set_target_properties(particle_simulation_vectorized.x PROPERTIES COMPILE_DEFINITIONS " OPTIMIZED=1 ")

if(Boost_FOUND)
	target_link_libraries(particle_simulation.x ${Boost_LIBRARIES})
endif()

if(Boost_FOUND)
	enable_testing ()
	set(ENV{CTEST_OUTPUT_ON_FAILURE} TRUE)
	
include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src/test)

	add_library(particle_simulation_test_lib STATIC ${sources} )
	
	add_test(NAME particle_simulation1.x 
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Testing/Binary 
                 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/particle_simulation.x
                 --algorithm=LENNARD_JONES
                 --data_structure=LINKED_CELLS
                 --input=GENERATOR_GRID_DISTRIBUTION
                 --count=100 
                 --output=FILE_CSV
                 --max_iterations=10 
                 --write_fequency=1 
                 --cut_off_radius=2.5
                 --timestep=0.005
                 --bounds=5/5/5)
    add_test(NAME particle_simulation2.x 
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Testing/Binary 
                 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/particle_simulation.x
                 --algorithm=LENNARD_JONES
                 --data_structure=LINKED_CELLS
                 --input=GENERATOR_GRID_DISTRIBUTION
                 --count=100 
                 --output=FILE_CSV
                 --max_iterations=10 
                 --write_fequency=1 
                 --cut_off_radius=1
                 --timestep=0.005
                 --bounds=10/10/10)
                 
	if(APPLE)
		set_target_properties(particle_simulation_test_lib PROPERTIES LINK_FLAGS "--coverage")
		target_link_libraries(particle_simulation_test_lib ${Boost_LIBRARIES})
	else()
		target_link_libraries(particle_simulation_test_lib ${Boost_LIBRARIES} gcov)
	endif()
	set_target_properties(particle_simulation_test_lib PROPERTIES COMPILE_FLAGS "-O0 -g -fprofile-arcs -ftest-coverage")
	set_target_properties(particle_simulation_test_lib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Testing/Binary)
	file(GLOB_RECURSE test_sources src/test*.cpp)
	foreach(testSrc ${test_sources})	        
		get_filename_component(testName ${testSrc} NAME_WE)
        add_executable(${testName}.x ${testSrc})
        if(APPLE)
		set_target_properties(${testName}.x PROPERTIES LINK_FLAGS "--coverage")
			target_link_libraries(${testName}.x ${Boost_LIBRARIES} particle_simulation_test_lib)
		else()
			target_link_libraries(${testName}.x ${Boost_LIBRARIES} particle_simulation_test_lib gcov)
		endif()
        
        set_target_properties(${testName}.x PROPERTIES COMPILE_FLAGS "-O0 -g -fprofile-arcs -ftest-coverage")
		set_target_properties(${testName}.x PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Testing/Binary)
        add_test(NAME ${testName}.x 
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Testing/Binary 
                 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/Testing/Binary/${testName}.x)
	endforeach()
	add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} 
	--verbose
	)
endif()
