# This works only with 15puzzle with a star and manhattan heuristic

import sys
import os
import subprocess

if len(sys.argv) != 3:
	print("Usage: python 15puzzle_executer.py input_file output_file")

input_file = open(sys.argv[1], 'r')
output_file = open(sys.argv[2], 'w')
output_file.write("grupo, algorithm, domain, instance, cost,h0, generated, time, gen_per_sec\n")

# Creates tmp file for the program to write in
tmp_out = open('tmp_out','w')
tmp_out.close()

for line in input_file:
	print("Now executing test: " + line)
	tmp_in = open('tmp_in','w')
	tmp_in.write(line)
	tmp_in.close()
	command = "sh -c \"ulimit -v 2097152 && ./15puzzle.a_starMan tmp_in tmp_out\""
	process = subprocess.Popen(command,shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	process.communicate()
	tmp_out = open('tmp_out','r')

	if process.returncode == 0:
		# process execution finalizes with sucess
		newline = tmp_out.readlines()[1]
	else:
		# Something went wrong (most probably mem stuff)
		newline = "x, astar, entrada, '"+ line[:-1] +"', na, na, na, na, na\n"
	output_file.write(newline)
	print("Done.")
	tmp_out.close()

	# deletes the in tmp file and creates it again in next iteration
	os.remove("tmp_in")

os.remove("tmp_out")
input_file.close()
output_file.close()