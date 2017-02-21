#!/bin/bash

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti_denser2_32k.sh -r 1 -R opti_denser2_32k_denser2_results particle_sim_opti.x "--count 32768 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 30/30/30 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal_denser2_32k.sh -r 1 -R normal_denser2_32k_denser2_results particle_simulation.x "--count 32768 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 30/30/30 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"


./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti_denser2_48k.sh -r 1 -R opti_denser2_48k_denser2_results particle_sim_opti.x "--count 42875 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 30/30/30 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal_denser2_48k.sh -r 1 -R normal_denser2_48k_denser2_results particle_simulation.x "--count 42875 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 30/30/30 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti_denser2_27k.sh -r 1 -R opti_denser2_27k_denser2_results particle_sim_opti.x "--count 27000 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 30/30/30 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal_denser2_27k.sh -r 1 -R normal_denser2_27k_denser2_results particle_simulation.x "--count 27000 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 30/30/30 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

