#!/bin/bash
./slurm_gprof_profiling.sh -s -t 10 -o run_gprof_opti -R opti_results particle_sim_opti.x "--count 800 --data_structure=GRID -m 10000 -r 4.0 -b 30/30/30 --output=FILE_CSV -t 0.01 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 10 -o run_gprof_normal -R normal_results particle_simulation.x "--count 800 --data_structure=GRID -m 10000 -r 4.0 -b 30/30/30 --output=FILE_CSV -t 0.01 --input=GENERATOR_GRID_DISTRIBUTION"

