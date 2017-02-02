
add_job(){
var_datastructure=$1
var_radius=$2
var_bounds=$3
var_initial_speed=$4
var_radius_extra=$5
var_threads=$6

var_test_name="simulation_${var_datastructure}_${var_radius}_${var_bounds}_${var_initial_speed}_${var_radius_extra}_${var_threads}"
cat > "job_script_${var_test_name}.sh" << EOF
#!/bin/bash
#SBATCH --time=01:00:00
#SBATCH -J projekt-${var_test_name}
#SBATCH -o ${var_test_name}.out
#SBATCH -p west
#SBATCH -c ${var_threads}
#SBATCH -N 1-1
#SBATCH -n 1
rm -rf out_64000_particles
srun hostname
srun ../../../particle_simulation.x \
--algorithm=LENNARD_JONES \
--data_structure=${var_datastructure} \
--input=GENERATOR_GRID_DISTRIBUTION --count=64000 \
--output=FILE_CSV --out_file_name="${var_test_name}.data" \
--max_iterations=2000 \
--write_fequency=1000 \
--cut_off_radius=${var_radius} \
--timestep=0.0005 \
--bounds=${var_bounds}/${var_bounds}/${var_bounds} \
--speed=${var_initial_speed} \
--cut_off_extra_factor=${var_radius_extra} \
--threads=${var_threads} \
--verbose
EOF
chmod +x "job_script_${var_test_name}.sh"
}

var_threads=24

for var_datastructure in "GRID" "GRID_LIST";
do

add_job $var_datastructure 6 60 0 1.2 $var_threads
add_job $var_datastructure 8 80 0 1.2 $var_threads
add_job $var_datastructure 12 120 0 1.2 $var_threads
add_job $var_datastructure 24 240 0 1.2 $var_threads
add_job $var_datastructure 6 60 1 1.2 $var_threads
add_job $var_datastructure 8 80 1 1.2 $var_threads
add_job $var_datastructure 12 120 1 1.2 $var_threads
add_job $var_datastructure 24 240 1 1.2 $var_threads
add_job $var_datastructure 6 60 0 1 $var_threads
add_job $var_datastructure 8 80 0 1 $var_threads
add_job $var_datastructure 12 120 0 1 $var_threads
add_job $var_datastructure 24 240 0 1 $var_threads
add_job $var_datastructure 6 60 1 1 $var_threads
add_job $var_datastructure 8 80 1 1 $var_threads
add_job $var_datastructure 12 120 1 1 $var_threads
add_job $var_datastructure 24 240 1 1 $var_threads

done
