format:
	clang-format -i -sort-includes *.cpp
	clang-format -i -sort-includes *.hpp

clean:
	cd .. && $(MAKE) clean
	rm -rf ../CMakeFiles
	rm -f ../CMakeCache.txt
	rm -f ../Makefile
	rm -f ../cmake_install.cmake

cmake:
	cd .. && cmake .
	cd .. && $(MAKE)

build:
	cd .. && $(MAKE)
	
run:
	cd .. && $(MAKE)
	cd .. && ./particle_simulation.x