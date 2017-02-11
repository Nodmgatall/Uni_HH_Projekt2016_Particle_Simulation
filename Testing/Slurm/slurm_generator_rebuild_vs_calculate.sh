
add_job(){
var_datastructure=$1
var_radius=$2
var_bounds=$3
var_initial_speed=$4
var_radius_extra=$5
var_threads=$6
var_iteration=$7

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

srun hostname
srun ../../../particle_simulation.x \
--algorithm=LENNARD_JONES \
--data_structure=${var_datastructure} \
--input=GENERATOR_GRID_DISTRIBUTION --count=64000 \
--output=VOID \
--max_iterations=${var_iteration} \
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

var_threads=11

for var_datastructure in "LINKED_CELLS" "LINKED_CELLS+NEIGHBOR_LIST";
do

for var_initial_speed in 1;
do

for var_radius_extra in 1.2;
do

for var_bounds in 80;
do

add_job $var_datastructure 2 $var_bounds $var_initial_speed $var_radius_extra $var_threads 2000
add_job $var_datastructure 4 $var_bounds $var_initial_speed $var_radius_extra $var_threads 1500
add_job $var_datastructure 8 $var_bounds $var_initial_speed $var_radius_extra $var_threads 800
add_job $var_datastructure 12 $var_bounds $var_initial_speed $var_radius_extra $var_threads 500
add_job $var_datastructure 16 $var_bounds $var_initial_speed $var_radius_extra $var_threads 400

done
done
done
done
