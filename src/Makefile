all: format
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

run: format
	cd .. && $(MAKE)
	cd .. && ./particle_simulation.x
	
rmlog: format
	rm -rf ../logdata