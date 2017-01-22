#!/bin/bash
#SBATCH -J particle-simulation
#SBATCH -o particle-simulation-grid-test-64000.out
#SBATCH -p west
#SBATCH -c 1
#SBATCH -N 1-1
#SBATCH -n 1
rm -rf out_64000_particles
srun hostname
srun ../../particle_simulation.x \
--algorithm=LENNARD_JONES \
--data_structure=GRID \
--input=GENERATOR_GRID_DISTRIBUTION --count=64000 \
--output=FILE_CSV --out_file_name="out_64000_particles" \
--max_iterations=20 \
--write_fequency=2000000 \
--cut_off_radius=2.5 \
--timestep=0.005 \
--bounds=50/50/50 \
--verbose
