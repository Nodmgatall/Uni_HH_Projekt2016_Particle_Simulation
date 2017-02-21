#!/bin/bash
./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti_64k.sh -r 1 -R opti_64k_results particle_sim_opti.x "--count 59319 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 60/60/60 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal_64k.sh -r 1 -R normal_64k_results particle_simulation.x "--count 59319 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 60/60/60 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"


./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti_32k.sh -r 1 -R opti_32k_results particle_sim_opti.x "--count 32768 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 60/60/60 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal_32k.sh -r 1 -R normal_32k_results particle_simulation.x "--count 32768 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 60/60/60 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"


./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti_48k.sh -r 1 -R opti_48k_results particle_sim_opti.x "--count 42875 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 60/60/60 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal_48k.sh -r 1 -R normal_48k_results particle_simulation.x "--count 42875 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 60/60/60 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti_80k.sh -r 1 -R opti_80k_results particle_sim_opti.x "--count 79507 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 60/60/60 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal_80k.sh -r 1 -R normal_80k_results particle_simulation.x "--count 79507 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 60/60/60 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti_27k.sh -r 1 -R opti_27k_results particle_sim_opti.x "--count 27000 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 60/60/60 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal_27k.sh -r 1 -R normal_27k_results particle_simulation.x "--count 27000 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 60/60/60 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

