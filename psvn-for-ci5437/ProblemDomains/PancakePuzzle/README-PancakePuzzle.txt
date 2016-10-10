DESCRIPTION
In the Pancake Puzzle there are N pancakes (identified with the numbers 0 to N-1).
A state is a permutation of the pancakes.
There are N-1 operators.  The i^th operator reverse the first i+1 positions in the given state.
For example, the 2nd operator reverses the first 3 positions, i.e. transforms state <0,1,2,3,4,5,6>
to state <2,1,0,3,4,5,6>.  The (N-1)th operator reverses the whole state (<0,1,2,3,4,5,6> becomes
<6,5,4,3,2,1,0>).


KEY PROPERTIES
All N! permutations (states) are reachable from any given state.
Each operator is its own inverse.
The maximum number of moves needed to transform one state into another is not exactly known; the best
theoretically proven upper bound is N*18/11.


GENERATOR
There is one generator in this directory, genPancake.
It uses the "standard" encoding, which has one state variable for each location in the puzzle and the
value of that location says which pancake is currently in that location.

Supports three cost models:
   -- unifom (all operators cost the same)
   -- random (each operator's cost is generated uniformly at random in a user-specified range)
   -- "pcost" model, which is specific to the pancake puzzle.  Every operator moves a pancake (call it p_out)
      out of the leftmost position and moves some other pancake (call it p_in) into the leftmost position.
      In the pcost model there is and NxN cost matrix containing values generated uniformly at random in a
      user-specified range, and the cost of an operator is cost[p_out][p_in] -- i.e. the cost of an operator
      depends on the state to which it is applied. For example, if the state is <2,1,0,3> then reversing the
      first three positions would have a cost of costs[2][0].  Reversing the first three positions immediately
      afterwards would have a cost of costs[0][2], which might be different.
      When this cost model is specified the number of PSVN rules increases by a factor of N^2 because the
      PSVN rule must specifiy particular values for p_in and p_out.


Command line options for genPancake:
If you do not have --pcost as the first command line argument, you must provide 1, 2, or 4 integers
on the command line.
The first integer is the number of pancakes.
If there are no other integers, operator costs will all be 1.
If there is one other integer, operator costs will all be that value.
If there are three additional integers, operator costs will be generated at random, and
these three integers are: the minimum cost, the maximum cost, and the random number seed.
If you have --pcost as the first command line argument, it must be followed by 4 integers as described above.


REFERENCE
http://en.wikipedia.org/wiki/Pancake_sorting

NOTES
1. In the theoretical literature the problem is often called "sorting by prefix reversals".
2. The generator provided here does not deal with the "burnt pancake" puzzle, but could be easily extended to do so.
