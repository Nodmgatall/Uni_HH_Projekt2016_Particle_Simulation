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

build: format
	cd .. && $(MAKE) -j 8 --no-print-directory

rmlog: format
	rm -rf ../logdata

run_64_particles: build_release
	cd .. && ./particle_simulation.x \
			--algorithm=LENNARD_JONES \
			--data_structure=GRID \
			--input=GENERATOR_GRID_DISTRIBUTION --count=64 \
			--output=FILE_CSV --out_file_name="logdata/out_64_particles"\
			--max_iterations=2000 \
			--write_fequency=1 \
			--cut_off_radius=2.5 \
			--timestep=0.005 \
			--bounds=5/5/5 \
			--verbose
run_64000_particles: build_release
	cd .. && ./particle_simulation.x \
			--algorithm=LENNARD_JONES \
			--data_structure=GRID \
			--input=GENERATOR_GRID_DISTRIBUTION --count=64000 \
			--output=FILE_CSV --out_file_name="logdata/out_64000_particles"\
			--max_iterations=2000 \
			--write_fequency=1 \
			--cut_off_radius=2.5 \
			--timestep=0.005 \
			--bounds=50/50/50 \
			--verbose
run_343_particles: build_release
	cd .. && ./particle_simulation.x \
			--algorithm=LENNARD_JONES \
			--data_structure=GRID \
			--input=GENERATOR_GRID_DISTRIBUTION --count=343 \
			--output=FILE_CSV --out_file_name="logdata/out_343_particles"\
			--max_iterations=7000 \
			--write_fequency=1 \
			--cut_off_radius=14 \
			--timestep=0.025 \
			--bounds=20.5/20.5/20.5 \
			--verbose
run_2_particles: build_release
	rm -rf ../logdata/2_particles
	cd .. && ./particle_simulation.x \
			--algorithm=LENNARD_JONES \
			--data_structure=GRID \
			--input=FILE_CSV --in_file_name="./Testing/Resources/2_particles.csv" \
			--output=FILE_CSV+AVI --out_file_name="logdata/out_2_particles"\
			--max_iterations=7090 \
			--write_fequency=10 \
			--cut_off_radius=2.5 \
			--timestep=0.005 \
			--bounds=4/4/4 \
			--verbose
run_2_particles_periodic_boundary: build_release
	rm -rf ../logdata/2_particles
	cd .. && ./particle_simulation.x \
			--algorithm=LENNARD_JONES \
			--data_structure=GRID \
			--input=FILE_CSV --in_file_name="./Testing/Resources/2_particles_periodic_boundary.csv" \
			--output=FILE_CSV --out_file_name="logdata/out_2_particles_boundary"\
			--max_iterations=7090 \
			--write_fequency=10 \
			--cut_off_radius=2.5 \
			--timestep=0.005 \
			--bounds=10/10/10 \
			--verbose

run_6_particles: build_release
	rm -rf ../logdata/6_particles
	cd .. && ./particle_simulation.x \
			--algorithm=LENNARD_JONES \
			--data_structure=GRID \
			--input=FILE_CSV --in_file_name="./Testing/Resources/6_particles.csv" \
			--output=FILE_CSV+AVI --out_file_name="logdata/out_6_particles"\
			--max_iterations=7090 \
			--write_fequency=10 \
			--cut_off_radius=2.5 \
			--timestep=0.005 \
			--bounds=5/5/5 \
			--verbose


run_2_particles_list: build_release
	rm -rf ../logdata/2_particles
	cd .. && ./particle_simulation.x --algorithm=LENNARD_JONES --data_structure=GRID --input=FILE_CSV  --in_file_name="./Testing/Resources/2_particles.csv" --output=FILE_CSV+AVI --max_iterations=7090  --write_fequency=10  --cut_off_radius=2.5 --timestep=0.005 --bounds=4/4/4 --verbose
	
run_6_particles_list: build_release
	rm -rf ../logdata/6_particles
	cd .. && ./particle_simulation.x --algorithm=LENNARD_JONES --data_structure=GRID --input=FILE_CSV  --in_file_name="./Testing/Resources/6_particles.csv" --output=FILE_CSV+AVI --max_iterations=709000  --write_fequency=10  --cut_off_radius=2.5 --timestep=0.005 --bounds=5/5/5 --verbose

test_grid:
	rm -rf ../Testing/Binary/*
	rm -rf ../Testing/Temporary/*
	rm -rf ../Testing/Coverage
	mkdir ../Testing/Coverage
	$(MAKE) cmake build 
	../Testing/Binary/test_DatastructureBaseForGrid.x
	../Testing/Binary/test_DatastructureGrid.x

test: 
	rm -rf ../Testing/Binary/*
	rm -rf ../Testing/Temporary/*
	rm -rf ../Testing/Coverage
	mkdir ../Testing/Coverage
	$(MAKE) cmake build 
	lcov --directory ../CMakeFiles/ --capture --initial --output-file ../Testing/Coverage/coverage_init.info
	-cd .. && $(MAKE) check
	lcov --directory ../CMakeFiles/ --capture --output-file ../Testing/Coverage/coverage_test.info
	lcov --add-tracefile ../Testing/Coverage/coverage_init.info --add-tracefile ../Testing/Coverage/coverage_test.info --output-file ../Testing/Coverage/coverage_combined.info
	lcov --extract ../Testing/Coverage/coverage_combined.info "*/src/main/*" --output-file ../Testing/Coverage/coverage.info
	genhtml ../Testing/Coverage/coverage.info --output-directory ../Testing/Coverage/coverage_out --demangle-cpp
	
code_coverage_only:
	lcov --directory ../CMakeFiles/ --capture --output-file ../Testing/Coverage/coverage_test.info
	lcov --add-tracefile ../Testing/Coverage/coverage_init.info --add-tracefile ../Testing/Coverage/coverage_test.info --output-file ../Testing/Coverage/coverage_combined.info
	lcov --extract ../Testing/Coverage/coverage_combined.info "*/src/main/*" --output-file ../Testing/Coverage/coverage.info
	genhtml ../Testing/Coverage/coverage.info --output-directory ../Testing/Coverage --demangle-cpp

show_log:
	cat ../Testing/Temporary/LastTest.log
