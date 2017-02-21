#!/bin/bash
./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti_denser_64k.sh -r 1 -R opti_denser_64k_denser_results particle_sim_opti.x "--count 59319 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 45/45/45 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal_denser_64k.sh -r 1 -R normal_denser_64k_denser_results particle_simulation.x "--count 59319 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 45/45/45 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"


./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti_denser_32k.sh -r 1 -R opti_denser_32k_denser_results particle_sim_opti.x "--count 32768 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 45/45/45 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal_denser_32k.sh -r 1 -R normal_denser_32k_denser_results particle_simulation.x "--count 32768 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 45/45/45 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"


./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti_denser_48k.sh -r 1 -R opti_denser_48k_denser_results particle_sim_opti.x "--count 42875 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 45/45/45 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal_denser_48k.sh -r 1 -R normal_denser_48k_denser_results particle_simulation.x "--count 42875 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 45/45/45 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti_denser_80k.sh -r 1 -R opti_denser_80k_denser_results particle_sim_opti.x "--count 79507 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 45/45/45 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal_denser_80k.sh -r 1 -R normal_denser_80k_denser_results particle_simulation.x "--count 79507 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 45/45/45 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_opti_denser_27k.sh -r 1 -R opti_denser_27k_denser_results particle_sim_opti.x "--count 27000 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 45/45/45 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

./slurm_gprof_profiling.sh -s -t 120 -o run_gprof_normal_denser_27k.sh -r 1 -R normal_denser_27k_denser_results particle_simulation.x "--count 27000 --data_structure=LINKED_CELLS -m 500 -r 6.0 -b 45/45/45 --cut_off_extra_factor=1.2 --threads=1 --output=FILE_CSV -t 0.000125 --input=GENERATOR_GRID_DISTRIBUTION"

