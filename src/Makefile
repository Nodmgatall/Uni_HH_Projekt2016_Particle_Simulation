all: format cmake build run

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
	cd .. && cmake .

build: format
	cd .. && $(MAKE)

rmlog: format
	rm -rf ../logdata
	
run: build
	cd .. && ./particle_simulation.x -p 27 -l 10 -f 2
