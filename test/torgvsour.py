import argparse
import os
from tcorewar import create_cmd
import time
import math

def time_versus(champ_a, champ_b, v_flag=0):
	to_run_org = create_cmd(champ_a, champ_b, v_flag=v_flag)
	to_run_our = create_cmd(champ_a, champ_b, is_org=False, v_flag=v_flag)

	os.system(f"TIMEFORMAT='%U %S'; (time {to_run_org}) > /dev/null 2> file_time_org")
	os.system(f"TIMEFORMAT='%U %S'; (time {to_run_our}) > /dev/null 2> file_time_our")

	with open('file_time_org', 'r') as file_org:
		raw_org = file_org.readline()
	with open('file_time_our', 'r') as file_our:
		raw_our = file_our.readline()

	val_org = round(sum(map(float, raw_org.split(' '))), 4)
	val_our = round(sum(map(float, raw_our.split(' '))), 4)

	diff = math.fabs(val_org - val_our)
	rlt = f"🏆 ( {diff:.3f} ) ◾️ " if val_our > val_org else f"◾ ( {diff:.3f} ) 🏆 "
	winner = 'org' if val_our > val_org else 'our'
	return (f"{val_org:.3f} -org- {rlt} -our- {val_our:.3f}", winner)

if __name__ == "__main__":
	parser = argparse.ArgumentParser()
	parser.add_argument('champs', nargs=2, help="champs name with .cor")
	parser.add_argument('-v', '--v_flag', help="v_flag", type=int, default=0)
	args = parser.parse_args()
	champ_a = args.champs[0]
	champ_b = args.champs[1]
	v_flag = args.v_flag

	print(time_versus(champ_a, champ_b, v_flag)[0])

#python torgvsour.py Asombra.cor doge.cor -v 0
