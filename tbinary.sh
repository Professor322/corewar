#!/bin/sh
flag_v='false'
floor=0
dump_max=40000
tal=0
echo "example:"
echo "./tbinary.sh -a Asombra -b Explosive_Kitty -v"
echo "job:"
while getopts 'a:b:d:f:v' opts; do
	case "${opts}" in
		a) name1=${OPTARG} ;;
		b) name2=${OPTARG} ;;
		d) dump_max=${OPTARG} ;;
    f) from=${OPTARG} ;;
    v) flag_v='true' ;;
	esac
done
#name1='jumper'
#name2='jumper'
#dump=1

run_compare() {
  diff='diff control our'
  control_paths="./vm_champs/corewar vm_champs/champs/$name1.cor vm_champs/champs/$name2.cor"
  our_paths="./cmake-build-debug/corewar vm_champs/champs/$name1.cor vm_champs/champs/$name2.cor"

  if ${flag_v}; then
    control_paths="${control_paths} -v 6"
    our_paths="${our_paths} -v"
  fi
  control="$control_paths -d $dump"
  our="$our_paths -dump $dump"

  echo " $dump"
  eval "$control" > control
  eval "$our" > our
  diff_res=$(eval $diff)
    if [ "${diff_res}" ]; then
        echo "       - diff control our  ⚠️"
    else
        echo "       - diff control our  ✅️"
    fi
}

dump_mem=$floor
dump=$(( ( ( $dump_max - $floor ) / 2 ) + $floor ))
while [ "$dump" -ne "$dump_mem" ]
do
  dump_mem=$dump
  run_compare
  if [ "${diff_res}" ]; then
        dump_max=$dump
    else
        floor=$dump
  fi
  dump=$(( (($dump_max - $floor) / 2) + $floor ))
done
echo "./test.sh -a $name1 -b $name2 -f $dump -t 8 -v"


