#!/bin/sh
path_our_corewar="../corewar"
path_org_corewar="./original_n_champs/corewar"
path_dir_champs="original_n_champs/champs/"


flag_v=0
from=1
tal=0
dump_max=100000
echo "example:"
echo "./test.sh -a big_feet -b bee_gees -d 4000 -v 6 -f 100"
echo
while getopts 'a:b:d:v:f:t:' opts; do
	case "${opts}" in
		a) name1=${OPTARG} ;;
		b) name2=${OPTARG} ;;
		d) dump_max=${OPTARG} ;;
    v) flag_v=${OPTARG} ;;
    f) from=${OPTARG} ;;
    t) tal=${OPTARG} ;;
	esac
done
#name1='jumper'
#name2='jumper'
#dump=1

diff='diff control our'

echo "work from $from to $dump_max:"

control_paths="$path_org_corewar $path_dir_champs$name1.cor $path_dir_champs$name2.cor"
our_paths="$path_our_corewar $path_dir_champs$name1.cor $path_dir_champs$name2.cor"


if (( $flag_v > 0 )); then
  control_paths="${control_paths} -v ${flag_v}"
  our_paths="${our_paths} -v ${flag_v}"
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
	last_line=$(tail -1 control)
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
	elif [[ $last_line == *"has won"* ]]; then
        echo "diff control our ✅  End of game 🏁️"
        break
	else
	    echo "diff control our ✅️"
	fi
done
echo
echo "$control_paths -d $dump"
echo "$our_paths -dump $dump"
