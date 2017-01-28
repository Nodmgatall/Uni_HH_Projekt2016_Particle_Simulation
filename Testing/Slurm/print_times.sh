echo "radius,bounds,initial_speed,total_rebuild_count,GRID_time_1,GRID_time_2,GRID_time_3,LISTEDGRID_time_1,LISTEDGRID_time_2,LISTEDGRID_time_3"
for var_radius in 2.5 3.0 5.0;
do
for var_bounds in 40 50 70 120;
do
if (( $(echo "(($var_radius < 5.0) || ($var_bounds >= 70))" |bc -l) )); then
for var_initial_speed in 0 0.5 1 5;
do
var_line_statistics_total_runtime="";
var_line_statistics_total_datastructure_rebuild_count="";
for var_run_index in 1 2 3;
do
for var_datastructure in "GRID" "LISTEDGRID";
do
var_test_name="simulation_${var_datastructure}_${var_radius}_${var_bounds}_${var_initial_speed}"
file_content=$(cat "${var_run_index}/${var_test_name}.out")
#abborted=$(echo "${file_content}" | grep  "Job step aborted")
statistics_total_runtime=$(echo "${file_content}" | grep "statistics.total_runtime" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
statistics_total_datastructure_rebuild_count=$(echo "${file_content}" | grep "statistics.total_datastructure_rebuild_count" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')

aborted=$(echo "${file_content}" | grep "something went badly wrong")

if [[ $param = *[!\ ]* ]]; then
var_line_statistics_total_runtime="$var_line_statistics_total_runtime,$statistics_total_runtime"
var_line_statistics_total_datastructure_rebuild_count="$statistics_total_datastructure_rebuild_count"
else
var_line_statistics_total_runtime="$var_line_statistics_total_runtime,999999999"
fi


done
done
echo "${var_radius},${var_bounds},${var_initial_speed},${var_line_statistics_total_datastructure_rebuild_count}${var_line_statistics_total_runtime}"
done
fi
done
done
