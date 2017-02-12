
add_job(){
var_datastructure=$1
var_radius=$2
var_bounds=$3
var_initial_speed=$4
var_radius_extra=$5
var_threads=$6
var_iteration=$7
var_rebuild=$8

var_test_name="simulation_${var_datastructure}_${var_radius}_${var_bounds}_${var_initial_speed}_${var_radius_extra}_${var_threads}_${var_rebuild}"

var_rebuild_params=""
if [ "$var_rebuild" == "n" ]; then
var_rebuild_params=" --dry_run --max_iterations_between_datastructure_rebuild=99999999 "
else
var_rebuild_params=" --dry_run --max_iterations_between_datastructure_rebuild=1 "
fi


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
--verbose \
${var_rebuild_params}
EOF
chmod +x "job_script_${var_test_name}.sh"
}

var_threads=11

for var_datastructure in "LINKED_CELLS" "LINKED_CELLS+NEIGHBOR_LIST";
do

for var_initial_speed in 0;
do

for var_radius_extra in 1.2;
do

for var_bounds in 80;
do

for var_rebuild in 'r' 'n';
do

for var_radius in 2 4 6 8;
do

add_job $var_datastructure $var_radius $var_bounds $var_initial_speed $var_radius_extra $var_threads 2000 $var_rebuild

done
for var_radius in 16;
do

add_job $var_datastructure $var_radius $var_bounds $var_initial_speed $var_radius_extra $var_threads 500 $var_rebuild

done
done
done
done
done
done
