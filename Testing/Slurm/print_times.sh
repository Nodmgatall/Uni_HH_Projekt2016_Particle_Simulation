for f in simulation_*.out; do
content=$(cat ${f})
everything=$(echo "${content}" | grep "everything" | sed -e 's/[^0-9. ]*//g' -e  's/ \+/ /g')
abborted=$(echo "${content}" | grep  "Job step aborted")
if [[ $abborted = *[!\ ]* ]]; then
# time limit reached -> abborted
echo "${f} > -"
else
if [[ $everything = *[!\ ]* ]]; then
# time is printed
echo "${f} -> ${everything}"
else
# still running
echo "${f} > ?"
fi
fi
done
