#!/bin/sh

path="vm_champs/champs"
#path="vm_champs/test"
tm=1
source="0_tscan_timeout"
max_dump=100000
tmp_out="run_out"
tmp_run="run_tmp"

echo "example:"
echo "./tscan.sh -t 1 -s 0_tscan_timeout"

while getopts 't:s:' opts; do
	case "${opts}" in
		t) tm=${OPTARG} ;;
		s) source=${OPTARG} ;;
	esac
done

run_with_timeout() {
  f_val="./tbinary.sh -a $champ_a -b $champ_b -v 14 -d $max_dump"
  echo $f_val > $tmp_out
  $f_val > $tmp_run 2>&1 &
  PID=$!

  (sleep $tm ; kill -9 $PID &> /dev/null; echo "timeout_kill" >> $tmp_out;) &
  PID_KILLER=$!

  # for check use:  ps aux | grep 'name of program in f_val'
  wait $PID &> /dev/null

  kill -9 $PID_KILLER &> /dev/null
  wait $PID_KILLER 2>/dev/null

  pid_core=$(pgrep corewar)
  kill -9 $pid_core &> /dev/null
  wait $pid_core 2>/dev/null

  echo "done" >> $tmp_out
}

log_no_timeout() {
  name_test=$(tail -1 run_tmp)
  state=$(tail -2 run_tmp | head -1)
  if [[ $state == *"✅"* ]]; then
    echo $f_val >> ${tm}_tscan_done_diff_ok
    echo "\t✅"
  elif [[ $state == *"🏁"* ]]; then
    echo $name_test >> ${tm}_tscan_done_finish
    echo "\t🏁️"
  else
    echo $name_test >> ${tm}_tscan_done_diff_bad
    echo "\t⚠"
  fi
}

log() {
  name_test=$(head -1 run_out)
  is_time_out=$(head -2 run_out | tail -1)
  if [[ $is_time_out == *"timeout_kill"* ]]; then
    echo "$champ_a $champ_b" >> ${tm}_tscan_timeout
    echo "\t⌛️"
  else
    log_no_timeout
  fi
}

init() {
  rm 0_tscan_timeout 2> /dev/null
  for champ_a in $(ls $path | cut -d '.' -f 1)
  do
    for champ_b in $(ls $path | cut -d '.' -f 1)
    do
      echo "$champ_a $champ_b" >> 0_tscan_timeout
    done
  done
}

#init

echo "${tm}_tscan_done_finish" > ${tm}_tscan_done_finish
echo "${tm}_tscan_done_diff_ok" > ${tm}_tscan_done_diff_ok
echo "${tm}_tscan_done_diff_bad" > ${tm}_tscan_done_diff_bad
rm ${tm}_tscan_timeout 2> /dev/null

while read line; do
  echo "$line"
  champ_a=$(echo $line | cut -d ' ' -f 1)
  champ_b=$(echo $line | cut -d ' ' -f 2)
  run_with_timeout
  log
done < $source