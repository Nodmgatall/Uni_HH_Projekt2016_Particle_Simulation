#!/bin/bash
#SBATCH -J particle-simulation
#SBATCH -o particle-simulation-grid-test-64.out
#SBATCH -p west
#SBATCH -c 24
#SBATCH -N 1-1
#SBATCH -n 1
rm -rf out_64_particles
srun hostname
srun ../../particle_simulation.x \
--algorithm=LENNARD_JONES \
--data_structure=GRID \
--input=GENERATOR_GRID_DISTRIBUTION --count=64 \
--output=FILE_CSV --out_file_name="out_64_particles" \
--max_iterations=2000 \
--write_fequency=2000 \
--cut_off_radius=2.5 \
--timestep=0.005 \
--bounds=5/5/5 \
--verbose
