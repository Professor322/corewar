#!/bin/sh
flag_v=0
floor=0
dump_max=40000
tal=0
echo "example:"
echo "./tbinary.sh -a Asombra -b Explosive_Kitty -v 6"
echo "    -v N      : Verbosity levels, can be added together to enable several
                - 2 : Show cycles
                - 4 : Show operations (Params are NOT litteral ...)
                - 8 : Show deaths"
echo "job:"
while getopts 'a:b:d:f:v:' opts; do
	case "${opts}" in
		a) name1=${OPTARG} ;;
		b) name2=${OPTARG} ;;
		d) dump_max=${OPTARG} ;;
    f) from=${OPTARG} ;;
    v) flag_v=${OPTARG} ;;
	esac
done
#name1='jumper'
#name2='jumper'
#dump=1

run_compare() {
  diff='diff control our'
  control_paths="./vm_champs/corewar vm_champs/champs/$name1.cor vm_champs/champs/$name2.cor"
  our_paths="./cmake-build-debug/corewar vm_champs/champs/$name1.cor vm_champs/champs/$name2.cor"

  if (( $flag_v > 0 )); then
    control_paths="${control_paths} -v ${flag_v}"
    our_paths="${our_paths} -v ${flag_v}"
  fi
  control="$control_paths -d $dump"
  our="$our_paths -dump $dump"

  echo " $dump"
  eval "$control" > control
  eval "$our" > our
  last_line=$(tail -1 control)
  diff_res=$(eval $diff)
    if [ "${diff_res}" ]; then
        echo "       - diff control our  ⚠️"
        last_bad=$dump_mem
    elif [[ $last_line == *"has won"* ]]; then
        echo "       - diff control our  🏁"
    else
        echo "       - diff control our  ✅️"
    fi
}

dump_mem=$floor
#dump=$(( ( ( $dump_max - $floor ) / 2 ) + $floor ))
dump=$dump_max
while [ "$dump" -ne "$dump_mem" ]
do
  dump_mem=$dump
  run_compare
  if [ "${diff_res}" ]; then # difference exist
      dump_max=$dump
  elif [[ $last_line == *"has won"* ]]; then
      break
  else
      floor=$dump
  fi

  dump=$(( (($dump_max - $floor) / 2) + $floor ))
done

if [ "${last_bad}" ]; then
  echo " $last_bad"
  echo "       - diff control our  ⚠️"
fi

echo "./test.sh -a $name1 -b $name2 -t 8 -v $flag_v -f $dump"
