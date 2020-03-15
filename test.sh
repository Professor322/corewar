#!/bin/sh

while getopts 'a:b:d:' opts; do
	case "${opts}" in
		a) name1=${OPTARG} ;;
		b) name2=${OPTARG} ;;
		d) dump_max=${OPTARG} ;;
	esac
done
#name1='jumper'
#name2='jumper'
#dump=1

diff='diff control our'

echo "$dump_max"

control_paths="./vm_champs/corewar vm_champs/champs/$name1.cor vm_champs/champs/$name2.cor"
our_paths="./cmake-build-debug/corewar vm_champs/champs/$name1.cor vm_champs/champs/$name2.cor"
for dump in $( seq 1 $dump_max )
do
	echo "dump $dump"
	control="$control_paths -d $dump"
#	echo "CONTROL $control"
	our="$our_paths -dump $dump"
#	echo "OUR $our"
	eval "$control" > control
	eval "$our" > our
	echo "diff control our"
	diff_res=$(eval $diff)
	if [ "${diff_res}" ]; then 
		echo "$diff_res"
		exit 1 
	fi
done
