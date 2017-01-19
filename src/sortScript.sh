#!/bin/bash
shopt -s nullglob
FILES=data.*.csv
for f in $FILES
do
	echo "Processing $f file..."
	(head -n 1 $f && tail -n +2 $f | sort) > "sorted${f}"
	cat $f
done
