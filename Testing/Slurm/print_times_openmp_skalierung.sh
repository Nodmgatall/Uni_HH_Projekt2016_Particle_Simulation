echo "row,\
radius,\
bounds,\
initial_speed,\
extra_radius,\
threads,\
vectorized,\
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
LINKED_CELLS+NEIGHBOR_LIST_time_3,\
LINKED_CELLS_average_time,\
LINKED_CELLS+NEIGHBOR_LIST_average_time,\
LINKED_CELLS_speedup,\
LINKED_CELLS+NEIGHBOR_LIST_speedup"

var_speedup_grid_0=1;
var_speedup_grid_list_0=1;
var_row=1

add_job(){
var_trash=$1
var_radius=$2
var_bounds=$3
var_initial_speed=$4
var_radius_extra=$5
var_threads=$6
var_vectorized=$7

var_line_statistics_total_runtime="";
var_line_statistics_total_datastructure_rebuild_count="";
var_sum_square_times_grid=0;
var_sum_square_times_grid_list=0;
for var_datastructure in "LINKED_CELLS" "LINKED_CELLS+NEIGHBOR_LIST";
do
for var_run_index in 1 2 3;
do
var_test_name="simulation_${var_datastructure}_${var_radius}_${var_bounds}_${var_initial_speed}_${var_radius_extra}_${var_threads}${var_vectorized}"
file_content=$(cat "${var_run_index}/${var_test_name}.out")
statistics_total_runtime=$(echo "${file_content}" | grep "statistics.total_runtime" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
statistics_total_datastructure_rebuild_count=$(echo "${file_content}" | grep "statistics.total_datastructure_rebuild_count" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')

aborted=$(echo "${file_content}" | grep "something went badly wrong")

if [[ $aborted = *[!\ ]* ]]; then
var_line_statistics_total_datastructure_rebuild_count="$var_line_statistics_total_datastructure_rebuild_count,999999999"
var_line_statistics_total_runtime="$var_line_statistics_total_runtime,999999999"
if [ "$var_datastructure" == "LINKED_CELLS" ]; then
var_sum_square_times_grid=999999999
else
var_sum_square_times_grid_list=999999999
fi
else
var_line_statistics_total_datastructure_rebuild_count="$var_line_statistics_total_datastructure_rebuild_count,$statistics_total_datastructure_rebuild_count"
var_line_statistics_total_runtime="$var_line_statistics_total_runtime,$statistics_total_runtime"
if [ "$var_datastructure" == "LINKED_CELLS" ]; then
var_sum_square_times_grid=$(echo "scale=8; ${var_sum_square_times_grid} + ${statistics_total_runtime} * ${statistics_total_runtime}" | bc -l)
else
var_sum_square_times_grid_list=$(echo "scale=8; ${var_sum_square_times_grid_list} + ${statistics_total_runtime} * ${statistics_total_runtime}" | bc -l)
fi
fi


done
done
var_average_times_grid=$(echo "scale=8; sqrt( ${var_sum_square_times_grid} / 3)" | bc -l)
var_average_times_grid_list=$(echo "scale=8; sqrt( ${var_sum_square_times_grid_list} / 3)" | bc -l)

if [ ${var_threads} == 1 ]; then
var_speedup_grid_0=$var_average_times_grid
var_speedup_grid_list_0=$var_average_times_grid_list
fi
var_speedup_grid=$(echo "scale=8; ${var_speedup_grid_0} / ${var_average_times_grid}" | bc -l)
var_speedup_grid_list=$(echo "scale=8; ${var_speedup_grid_list_0} / ${var_average_times_grid_list}" | bc -l)

echo "${var_row},${var_radius},${var_bounds},${var_initial_speed},${var_radius_extra},${var_threads},${var_vectorized}${var_line_statistics_total_datastructure_rebuild_count}${var_line_statistics_total_runtime},$var_average_times_grid,$var_average_times_grid_list,$var_speedup_grid,$var_speedup_grid_list"
var_row=$((var_row + 1))
}
for var_vectorized in "" "_vectorized"
do
for var_datastructure in "LINKED_CELLS" "LINKED_CELLS+NEIGHBOR_LIST";
do
for var_cut_off in 1 1.2
do
for var_threads in `seq 1 24`
do
add_job $var_datastructure 8 80 0 $var_cut_off $var_threads $var_vectorized
done
done
done
done
