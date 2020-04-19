#!/bin/sh
flag_v='false'
from=1
tal=0
dump_max=100000
echo "example:"
echo "./test.sh -a big_feet -b bee_gees -d 4000 -v -f 100"
echo
while getopts 'a:b:d:vf:t:' opts; do
	case "${opts}" in
		a) name1=${OPTARG} ;;
		b) name2=${OPTARG} ;;
		d) dump_max=${OPTARG} ;;
    v) flag_v='true' ;;
    f) from=${OPTARG} ;;
    t) tal=${OPTARG} ;;
	esac
done
#name1='jumper'
#name2='jumper'
#dump=1

diff='diff control our'

echo "work from $from to $dump_max:"

control_paths="./vm_champs/corewar vm_champs/champs/$name1.cor vm_champs/champs/$name2.cor"
our_paths="./cmake-build-debug/corewar vm_champs/champs/$name1.cor vm_champs/champs/$name2.cor"

if ${flag_v}; then
  control_paths="${control_paths} -v 6"
  our_paths="${our_paths} -v"
fi

for dump in $( seq $from $dump_max )
do
	echo "dump $dump"
	control="$control_paths -d $dump"
#	echo "CONTROL $control"
	our="$our_paths -dump $dump"
#	echo "OUR $our"
	eval "$control" > control
	eval "$our" > our
	diff_res=$(eval $diff)
	if [ "${diff_res}" ]; then
	    echo "diff control our  ⚠️"
		  echo "$diff_res"
			echo "diff end          ⚠️"
			echo
		if [ "$tal" -ne "0" ]; then
		  real_tal=$(( $tal + 64 ))
      eval "tail -n $real_tal our | head -n $tal"
      echo
      echo "our - 👆  ###  👇 - original"
      echo
      eval "tail -n $real_tal control | head -n $tal"
      echo
    fi
		break
	else
	    echo "diff control our ✅️"
	fi
done
echo
echo "$control_paths -d $dump"
echo "$our_paths -dump $dump"
