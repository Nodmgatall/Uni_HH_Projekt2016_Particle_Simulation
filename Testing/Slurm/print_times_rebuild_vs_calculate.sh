echo "row,\
rebuild,\
iterations,\
dichte,\
particles_per_cell,\
cell_count,\
radius,\
bounds,\
initial_speed,\
extra_radius,\
threads,\
LINKED_CELLS_rebuild_count_1,\
LINKED_CELLS_rebuild_count_2,\
LINKED_CELLS_rebuild_count_3,\
LINKED_CELLS+NEIGHBOR_LIST_rebuild_count_1,\
LINKED_CELLS+NEIGHBOR_LIST_rebuild_count_2,\
LINKED_CELLS+NEIGHBOR_LIST_rebuild_count_3,\
LINKED_CELLS_time_1,\
LINKED_CELLS_time_2,\
LINKED_CELLS_time_3,\
LINKED_CELLS+NEIGHBOR_LIST_time_1,\
LINKED_CELLS+NEIGHBOR_LIST_time_2,\
LINKED_CELLS+NEIGHBOR_LIST_time_3"

var_row=1
add_job(){
var_datastructure=$1
var_radius=$2
var_bounds=$3
var_initial_speed=$4
var_radius_extra=$5
var_threads=$6
var_iteration=$7
var_rebuild=$8

var_line_statistics_total_runtime="";
var_line_statistics_total_datastructure_rebuild_count="";
var_line_cell_count="";
var_line_particles_per_cell="";
var_line_dichte="";
for var_datastructure in "LINKED_CELLS" "LINKED_CELLS+NEIGHBOR_LIST";
do
var_test_name="simulation_${var_datastructure}_${var_radius}_${var_bounds}_${var_initial_speed}_${var_radius_extra}_${var_threads}_${var_rebuild}"
for var_run_index in 1 2 3;
do
file_content=$(cat "${var_run_index}/${var_test_name}.out")
statistics_total_runtime=$(echo "${file_content}" | grep "statistics.total_runtime" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
statistics_total_datastructure_rebuild_count=$(echo "${file_content}" | grep "statistics.total_datastructure_rebuild_count" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')

var_line_cell_count=$(echo "${file_content}" | grep "statistics.m_cell_count" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
var_line_particles_per_cell=$(echo "${file_content}" | grep "statistics.particles_per_cell" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
var_line_dichte=$(echo "${file_content}" | grep "statistics.partikeldichte" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')

aborted=$(echo "${file_content}" | grep "something went badly wrong")

if [[ $aborted = *[!\ ]* ]]; then
var_line_statistics_total_datastructure_rebuild_count="$var_line_statistics_total_datastructure_rebuild_count,999999999"
var_line_statistics_total_runtime="$var_line_statistics_total_runtime,999999999"
else
var_line_statistics_total_datastructure_rebuild_count="$var_line_statistics_total_datastructure_rebuild_count,$statistics_total_datastructure_rebuild_count"
var_line_statistics_total_runtime="$var_line_statistics_total_runtime,$statistics_total_runtime"
fi


done
done

echo "${var_row},${var_rebuild},${var_iteration},${var_line_dichte},${var_line_particles_per_cell},${var_line_cell_count},${var_radius},${var_bounds},${var_initial_speed},${var_radius_extra},${var_threads}${var_line_statistics_total_datastructure_rebuild_count}${var_line_statistics_total_runtime}"
var_row=$((var_row + 1))
}

var_threads=11

for var_datastructure in "LINKED_CELLS";
do

for var_rebuild in 'r' 'n' 'b';
do

add_job $var_datastructure 6  60  0 1.2 $var_threads 3000 $var_rebuild
add_job $var_datastructure 8  80  0 1.2 $var_threads 3000 $var_rebuild
add_job $var_datastructure 12 120 0 1.2 $var_threads 3000 $var_rebuild
add_job $var_datastructure 24 240 0 1.2 $var_threads 3000 $var_rebuild
add_job $var_datastructure 6  60  1 1.2 $var_threads 3000 $var_rebuild
add_job $var_datastructure 8  80  1 1.2 $var_threads 3000 $var_rebuild
add_job $var_datastructure 12 120 1 1.2 $var_threads 3000 $var_rebuild
add_job $var_datastructure 24 240 1 1.2 $var_threads 3000 $var_rebuild
done
done

