#!/bin/bash
./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti.sh -r 1 -R opti_results particle_sim_opti.x "--count 64000 --data_structure=GRID -m 2000 -r 6.0 -b 60/60/60 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.0005 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal.sh -r 1 -R normal_results particle_simulation.x "--count 64000 --data_structure=GRID -m 2000 -r 6.0 -b 60/60/60 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.0005 --input=GENERATOR_GRID_DISTRIBUTION"

