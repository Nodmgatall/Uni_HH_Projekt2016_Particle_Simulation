
for var_datastructure in "GRID" "LISTEDGRID" "LIST_BENJAMIN";
do

for var_radius in 2.5 5.0 10.0 40.0;
do
var_int_radius=${var_radius%.*}

for var_bounds in 40 50 70;
do
var_int_bounds=${var_bounds%.*}

var_test_name="simulation_${var_datastructure}_${var_int_radius}_${var_int_bounds}"

cat > "job_script_${var_test_name}.sh" << EOF
#!/bin/bash
#SBATCH --time=00:30:00
#SBATCH -J projekt-${var_test_name}
#SBATCH -o ${var_test_name}.out
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
--output=FILE_CSV --out_file_name="${var_test_name}.data" \
--max_iterations=2000 \
--write_fequency=10 \
--cut_off_radius=${var_radius} \
--timestep=0.005 \
--bounds=${var_bounds}/${var_bounds}/${var_bounds} \
--verbose
EOF
chmod +x "job_script_${var_test_name}.sh"

done
done
done
