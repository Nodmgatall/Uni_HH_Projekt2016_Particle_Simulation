all: format cmake build run

format:
	find -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i -sort-includes
	find -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i -sort-includes

clean: format
	cd .. && $(MAKE) clean
	rm -rf ../CMakeFiles
	rm -f ../CMakeCache.txt
	rm -f ../Makefile
	rm -f ../cmake_install.cmake

cmake:
	cd .. && cmake .

build: format
	cd .. && $(MAKE)

rmlog: format
	rm -rf ../logdata
	
run: build
	cd .. && ./particle_simulation.x -p 27