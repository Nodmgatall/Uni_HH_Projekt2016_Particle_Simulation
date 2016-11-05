all: format cmake run
	cd .. && $(MAKE) clean
	cd .. && cmake .
	cd .. && $(MAKE)
	cd .. && ./particle_simulation.x

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
	cd .. && $(MAKE)

build: format
	cd .. && $(MAKE)

run: build
	cd .. && ./particle_simulation.x -p 10
	
rmlog: format
	rm -rf ../logdata