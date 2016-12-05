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
	cd .. && CC=clang-omp CXX=clang-omp++ cmake -G "Eclipse CDT4 - Unix Makefiles"
	cat ../.cproject | sed 's/199711L/201402L/g' > ../.cproject1; mv -f  ../.cproject1 ../.cproject
else
	cd .. && cmake -G "Eclipse CDT4 - Unix Makefiles"
	sed -i 's/199711L/201402L/g' ../.cproject
endif

build: format
	cd .. && $(MAKE) -j 8

rmlog: format
	rm -rf ../logdata

run: build
	cd .. && ./particle_simulation.x -p 100 -l 0.1 -f 1 -r 2.5 -t 0.005
