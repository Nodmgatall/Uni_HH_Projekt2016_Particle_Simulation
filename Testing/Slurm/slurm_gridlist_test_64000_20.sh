#!/bin/bash
#SBATCH --time=00:30:00
#SBATCH -J particle-simulation
#SBATCH -o particle-simulation-gridlist-test-64000-20.out
#SBATCH -p west
#SBATCH -c 24
#SBATCH -N 1-1
#SBATCH -n 1
rm -rf out_64000_particles
srun hostname
srun ../../particle_simulation.x \
--algorithm=LENNARD_JONES \
--data_structure=GRID \
--input=GENERATOR_GRID_DISTRIBUTION --count=64000 \
--output=FILE_CSV --out_file_name="out_64000_particles_gridlist_20.out" \
--max_iterations=2000 \
--write_fequency=10 \
--cut_off_radius=2.5 \
--timestep=0.005 \
--bounds=50/50/50 \
--max_iterations_between_datastructure_rebuild=20 \
--verbose
