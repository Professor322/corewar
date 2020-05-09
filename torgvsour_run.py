import os

with open("file_vs_finish", "r") as txt:
	lines = [next(txt).replace('tbinary.py', 'torgvsour.py') for x in range(100)]

[os.system(cmd) for cmd in lines]

#python torgvsour_run.py
