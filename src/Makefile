all: format cmake build run

platform=$(shell uname)

format:
	find . -maxdepth 10 -name "*.cpp" | xargs clang-format -i -sort-includes
	find . -maxdepth 10 -name "*.hpp" | xargs clang-format -i -sort-includes

clean: format
	cd .. && $(MAKE) clean
	rm -rf ../CMakeFiles
	rm -f ../CMakeCache.txt
	rm -f ../Makefile
	rm -f ../cmake_install.cmake
	rm -rf ../xml
	rm -rf ../html
	rm -rf ../latex

doxygen:
	cd .. && doxygen

cmake:
ifeq ($(platform),Darwin)
	cd .. && CC=clang-omp CXX=clang-omp++ cmake .
else
	cd .. && cmake .
endif
	
build: format
	cd .. && $(MAKE) -j 8

rmlog: format
	rm -rf ../logdata
	
run: build
	cd .. && ./particle_simulation.x -p 1000 -l 10 -f 2 -r 4 -t 0.5
