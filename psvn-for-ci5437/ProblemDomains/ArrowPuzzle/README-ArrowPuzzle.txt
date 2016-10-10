DESCRIPTION
In the Arrow Puzzle there are N arrows. In a given state, an arrow is either pointing up or pointing down.
There are N-1 operators.  The i^th operator flips arrows i and (i+1) (to "flip" an arrow means to reverse
its orientation -- if it was pointing up flipping it makes it point down, and vice versa).


KEY PROPERTIES
Only half of the 2^N states are reachable from any given state.
The operators all commute with one another and each operator is its own inverse.
The maximum number of moves needed to transform one state into another is N-1 (each operator needs to be used
	at most once).


GENERATORS
In this directory there are two generators for the Arrow puzzle, genArrowStd and genArrowSwap.

genArrowStd:
Uses the "standard" encoding of the puzzle, which has one binary state variable for
  each arrow indicating if the arrow is pointing down (0) or up (1).

Supports two cost models:
   -- unifom (all operators cost the same)
   -- random (each operator's cost is generated uniformly at random in a user-specified range)

Command line options for genArrowStd:
You must provide 1, 2, or 4 integers on the command line.
The first integer is the number of arrows.
If there are no other integers, operator costs will all be 1.
If there is one other integer, operator costs will all be that value.
If there are three additional integers, operator costs will be generated at random, and
these three integers are: the minimum cost, the maximum cost, and the random number seed.


genArrowSwap:
Uses the non-standard "swap" encoding of the puzzle, which has two binary state variables for
  each arrow: one of them holds the arrow's current value (0 if the arrow is pointing down,
  1 if it is pointing up), the other one holds the opposite value.  This allows an arrow
  to be flipped by swapping the values of its two variables.

Supports two cost models:
   -- unifom (all operators cost the same)
   -- random (each operator's cost is generated uniformly at random in a user-specified range)

The command line options for genArrowSwap are the same as for genArrowStd.


REFERENCE
Richard E. Korf (1980), Towards a Model of Representation Changes, Artificial Intelligence 14(1):41-78.
