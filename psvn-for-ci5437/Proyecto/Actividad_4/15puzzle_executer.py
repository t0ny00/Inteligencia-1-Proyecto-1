# This works only with 15puzzle with a star and manhattan heuristic

import sys
import os
import subprocess

if len(sys.argv) != 3:
	print("Usage: python 15puzzle_executer.py input_file output_file")

input_file = open(sys.argv[1], 'r')
output_file = open(sys.argv[2], 'w')

# Creates tmp file for the program to write in
tmp_out = open('tmp_out','w')
tmp_out.close()

for line in input_file:
	tmp_in = open('tmp_in','w')
	tmp_in.write(line)
	tmp_in.close()
	command = "sh -c \"ulimit -v 2097152 && ./15puzzle.a_starMan tmp_in tmp_out\""
	process = subprocess.Popen(command,shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	process.communicate()
	tmp_out = open('tmp_out','r')

	if process.returncode == 0:
		# process execution finalizes with sucess
		output_file.write(tmp_out.read())
	else:
		# Something went wrong (most probably mem stuff)
		output_file.write("x, astar, entrada, '"+ line +"', na, na, na, na, na")
	tmp_out.close()

	# deletes the in tmp file and creates it again in next iteration
	os.remove("tmp_in")

os.remove("tmp_out")
input_file.close()
output_file.close()