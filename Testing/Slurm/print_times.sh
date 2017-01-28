echo "radius,bounds,initial_speed,extra_radius,GRID_rebuild_count_1,GRID_rebuild_count_2,GRID_rebuild_count_3,GRID_LIST_rebuild_count_1,GRID_LIST_rebuild_count_2,GRID_LIST_rebuild_count_3,GRID_time_1,GRID_time_2,GRID_time_3,GRID_LIST_time_1,GRID_LIST_time_2,GRID_LIST_time_3"

add_job(){
var_trash=$1
var_radius=$2
var_bounds=$3
var_initial_speed=$4
var_radius_extra=$5

var_line_statistics_total_runtime="";
var_line_statistics_total_datastructure_rebuild_count="";
for var_datastructure in "GRID" "GRID_LIST";
do
for var_run_index in 1 2 3;
do
var_test_name="simulation_${var_datastructure}_${var_radius}_${var_bounds}_${var_initial_speed}_${var_radius_extra}"
file_content=$(cat "${var_run_index}/${var_test_name}.out")
statistics_total_runtime=$(echo "${file_content}" | grep "statistics.total_runtime" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
statistics_total_datastructure_rebuild_count=$(echo "${file_content}" | grep "statistics.total_datastructure_rebuild_count" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')

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
echo "${var_radius},${var_bounds},${var_initial_speed},${var_radius_extra},${var_line_statistics_total_datastructure_rebuild_count},${var_line_statistics_total_runtime}"

}

var_datastructure="GRID"

add_job $var_datastructure 2.5 40 0 1.2
add_job $var_datastructure 2.5 80 0 1.2
add_job $var_datastructure 2.5 120 0 1.2
add_job $var_datastructure 2.5 40 1 1.2
add_job $var_datastructure 2.5 80 1 1.2
add_job $var_datastructure 2.5 120 1 1.2
add_job $var_datastructure 8 40 0 1.2
add_job $var_datastructure 8 80 0 1.2
add_job $var_datastructure 8 120 0 1.2
add_job $var_datastructure 8 40 1 1.2
add_job $var_datastructure 8 80 1 1.2
add_job $var_datastructure 8 120 1 1.2
add_job $var_datastructure 8 40 0 1
add_job $var_datastructure 8 80 0 1
add_job $var_datastructure 8 120 0 1
add_job $var_datastructure 8 40 1 1
add_job $var_datastructure 8 80 1 1
add_job $var_datastructure 8 120 1 1

