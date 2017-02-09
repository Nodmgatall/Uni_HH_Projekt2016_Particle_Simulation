usage() { echo "usage" 1>&2; exit 1; }

##time -t
time=1
##number of nodes -N
num_nodes=1
##number of tasks -n
num_tasks=1
## result folder -R
result_folder="results"
## gmon.out name if saved
single_result_name="run_result"
## save gmon.out of each iteration -s
save_each_iteration=0
## $1
programm_name=""
## $2
## number of runs -r
number_of_runs=5
##partition -p
partition="west"
##dryrun -d
dryrun=0
##name of the created script
script_name=run_gprof.x
while getopts ":t:N:n:R:g:sr:p:do:" o; do

	case "${o}" in
		t)
			time=${OPTARG}
			;;
		N)	
			num_nodes=${OPTARG}
			;;
		n)
			num_tasks=${OPTARG}
			;;
		R)
			result_folder=${OPTARG}
			;;
		g)
			single_result_name=${OPTARG}
			;;
		s)
			save_each_iteration=1
			;;
		
		r)
			number_of_runs=${OPTARG}
			;;
		p)
			partition=${OPTARG}
			;;
		d)
			dryrun=1
			;;
		o)
			script_name=${OPTARG}
			;;
		*)
			usage
			;;
	esac
done
shift $((OPTIND -1))
if [[ -x "$1" ]]
then
echo "works"
else
echo "Error: $1 is no executable"
usage
fi

rm -rf ${result_folder}
mkdir ${result_folder}
echo "Setup: "
echo " -- time limit: ${time}"
echo " -- number of nodes: ${num_nodes}"
echo " -- number of tasks: ${num_tasks}"
echo " -- files are written to: ${result_folder}"
echo " -- executable: $1 $2"
echo " -- save iteration output: ${save_each_iteration}"
echo " -- number of runs: ${number_of_runs}"
echo " -- dryrun: ${dryrun}"
echo " -- srun -N ${num_nodes} -n ${num_tasks} $1 $2 "
cat > "${result_folder}/${script_name}" << EOF
#!/bin/bash
#SBATCH --time=${time}
#SBATCH --error=eerr.out --output=cout.out
#SBATCH -N ${num_nodes}-${num_nodes}
#SBATCH -n ${num_tasks}
#SBATCH --partition=${partition}
srun ../$1 $2 
gprof ../$1 > ${single_result_name}_0.out
mv gmon.out gmon.sum
for ((i = 1; i <= ${number_of_runs}; i++))
do
	srun ../$1 $2 
	if [[ ${save_each_iteration} == 1 ]]
	then
		gprof ../$1 > ${single_result_name}_\${i}.out
	fi
	gprof -s ../$1 gmon.out gmon.sum
done	
gprof ../$1 gmon.sum > summation_gprof.txt
EOF

chmod +x ${result_folder}/${script_name}
if [ ${dryrun} == 0 ]
then 
	cd ${result_folder}
	sbatch ${script_name}
	cd ..
fi
