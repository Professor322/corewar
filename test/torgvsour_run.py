from torgvsour import time_versus

limit = 10
vault = { 'org': 0, 'our': 0}

with open("file_vs_finish", "r") as txt:
	lines = []
	for line in txt:
		cmd = line.split(" ")
		lines.append((cmd[2], cmd[3][:-1]))
		limit -= 1
		if limit == 0:
			break


for idx, cmd in enumerate(lines):
	rlt = time_versus(cmd[0], cmd[1])
	vault[rlt[1]] += 1
	print(f"{rlt[0]}\t{idx:{6}}\t{cmd[0]} {cmd[1]}")

print(vault)
#python torgvsour_run.py
