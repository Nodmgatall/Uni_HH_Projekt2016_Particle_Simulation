.PHONY: all format clean doxygen cmake build rmlog run test show_log code_coverage_only

all: format cmake build run

platform=$(shell uname)

format:
	find . -maxdepth 10 -name "*.cpp" | xargs clang-format -i -sort-includes
	find . -maxdepth 10 -name "*.hpp" | xargs clang-format -i -sort-includes

clean: format
	cd .. && $(MAKE) clean --no-print-directory
	rm -rf ../CMakeFiles ../CMakeCache.txt ../Makefile ../cmake_install.cmake CTestTestfile.cmake ../xml ../html ../latex 

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

	
build_release: format
	cd .. && $(MAKE) particle_simulation.x -j 8 --no-print-directory

build: build_release
	cd .. && $(MAKE) -j 8 --no-print-directory

rmlog: format
	rm -rf ../logdata

run: build_release
	cd .. && ./particle_simulation.x -p 100 -l 0.1 -f 1 -r 2.5 -t 0.005

test: 
	rm -rf ../Testing
	$(MAKE) cmake build
	lcov --directory ../CMakeFiles/ --capture --initial --output-file ../Testing/coverage_init.info
	cd .. && $(MAKE) check
	lcov --directory ../CMakeFiles/ --capture --output-file ../Testing/coverage_test.info
	lcov --add-tracefile ../Testing/coverage_init.info --add-tracefile ../Testing/coverage_test.info --output-file ../Testing/coverage_combined.info
	lcov --extract ../Testing/coverage_combined.info "*/src/main/*" --output-file ../Testing/coverage.info
	genhtml ../Testing/coverage.info --output-directory ../Testing/coverage_out --demangle-cpp

code_coverage_only:
	lcov --directory ../CMakeFiles/ --capture --output-file ../Testing/coverage_test.info
	lcov --add-tracefile ../Testing/coverage_init.info --add-tracefile ../Testing/coverage_test.info --output-file ../Testing/coverage_combined.info
	lcov --extract ../Testing/coverage_combined.info "*/src/main/*" --output-file ../Testing/coverage.info
	genhtml ../Testing/coverage.info --output-directory ../Testing/coverage_out --demangle-cpp

show_log:
	cat ../Testing/Temporary/LastTest.log