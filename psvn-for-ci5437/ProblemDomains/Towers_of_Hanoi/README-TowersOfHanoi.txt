DESCRIPTION
In the Towers of Hanoi puzzle there are P distinct pegs and D disks, each disk a different size.
In a given state, each disk is on exactly one peg and the disks on a peg are in increasing size
from top to bottom.
An operator moves the top disk from one peg to the top of another peg.  An operator can only be applied
if the disk being moved is smaller than the top disk on the peg to which it is being moved.


KEY PROPERTIES
All of the P^D states are reachable from any given state if P > 2.
If there are 3 pegs, the maximum number of moves needed to transform one state into another is 2^D-1. If
   the number of pegs is greater than the number of disks, at most 2D-1 moves are needed.  Interesting things
   happen in between these two extremes.
If there are 3 pegs, there is a well-known recursive algorithm for optimally solving the problem of moving
   all the disks from one peg to another. No such algorithm is known for 4 or more pegs.


GENERATORS
In this directory there are two generators for the Towers of Hanoi. genHanoi3 is specific to the 3-peg
Towers of Hanoi; genHanoi works for any number of pegs (3 or more).

genHanoi3:
Generates PSVN for the Towers of Hanoi with 3 pegs and D disks.
Uses the following encoding of the puzzle, which is only efficient when there are 3 pegs.
   For each disk there will be one state variables indicating which peg
     the disk is on (possible values are 1, 2, and 3).
   The variable for the smallest disk is first, then the variable for the second smallest disk, etc.
  
   For each disk d and for each pair of pegs i and j one PSVN operator is needed for moving d
     from the top of peg i to the top of peg j.

Supports two cost models:
   -- unifom (all operators cost the same)
   -- random (each operator's cost is generated uniformly at random in a user-specified range)

Command line options for genHanoi3:
You must provide 1, 2, or 4 integers on the command line.
The first integer is the number of disks (2 or more).
If there are no other integers, operator costs will all be 1.
If there is one other integer, operator costs will all be that value.
If there are three additional integers, operator costs will be generated at random, and
these three integers are: the minimum cost, the maximum cost, and the random number seed.



genHanoi:
Generates PSVN for the Towers of Hanoi with P pegs and D disks.
Uses the following encoding of the puzzle:
   For each disk there will be P binary state variables indicating which peg the disk is on (if disk d
     is on peg i, the i^th state variable for d will be 1 and the others will be 0).
   The variables for the smallest disk are first, then the variables for the second smallest disk, etc.
  
   For each disk d and for each pair of pegs i and j one PSVN operator is needed for moving d
   from the top of peg i to the top of peg j.

Supports two cost models:
   -- unifom (all operators cost the same)
   -- random (each operator's cost is generated uniformly at random in a user-specified range)

Command line options for genHanoi:
You must provide 2, 3, or 5 integers on the command line.
The first integer is the number of pegs (3 or more).
The next integer is the number of disks (2 or more).
If there are no other integers, operator costs will all be 1.
If there is one other integer, operator costs will all be that value.
If there are three additional integers, operator costs will be generated at random, and
these three integers are: the minimum cost, the maximum cost, and the random number seed.



REFERENCE
Richard E. Korf and Ariel Felner (2007), "Recent Progress in Heuristic Search: A Case Study of the
Four-Peg Towers of Hanoi Problem", Proceedings of the International Joint Conference on Artificial
Intelligence (IJCAI-07), pp. 2334-2329.
