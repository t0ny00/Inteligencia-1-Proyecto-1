DESCRIPTION
TopSpin is a commercial puzzle made by Binary Arts.  There is a circular ring of N tokens (typically the
numbers 1 to N or 0 to N-1) and a special section of the ring (the "turntable" or "turnstile") of length K
(typically K=4) that can be "spun" to reverse the order of the K tokens in it. In the physical puzzle,
the ring of tokens has to be rotated to get the token you want to reverse into the turntable.
In most computer encodings (including the ones here), the rotation of the ring is not counted as a move,
you are free to reverse any K consecutive tokens at any time.


KEY PROPERTIES
If the tokens are all distinct then each state is a permutation. Exactly how many of the N! permutations (states)
can be reached from a given state depends on both N and K.  Chen and Skiena (see reference below) give a
complete characterization. In general, odd values of K are not as interesting as even values.

Each operator is its own inverse.

The number of moves needed to transform one state into another is not exactly known; Chen and Skiena give lower
and upper bounds.


GENERATORS
This directory contains two generators for TopSpin, genTopSpinBasic and genTopSpinCompact.

genTopSpinBasic:
In this encoding there are N state variables, one for each position of the puzzle. The value of a state variable
indicates which token is currently in that location.  Any four adjacent locations can be rotated (including locations
that are adjacent by "wrapping around" from the end of the vector to the beginning, e.g. there is an operator that
reverses the tokens in location N-2, N-1, 0, and 1 (assuming locations are numbered 0 to N-1).  Because only the
circular order of the tokens matters, in this encoding there are N goal states which differ only in their cyclic
rotation.  Note that vectors that differ only in their cyclic rotation are considered different so there are N!
different states even though there are only (N-1)! different cyclic orders of N tokens.

Command line options for genTopSpinBasic:
You must provide 2, 3, or 5 integers on the command line.
The first integer is the number of tokens. The second is the size of the turntable.
If there are no other integers, operator costs will all be 1.
If there is one other integer, operator costs will all be that value.
If there are three additional integers, operator costs will be generated at random, and
these three integers are: the minimum cost, the maximum cost, and the random number seed.



genTopSpinCompact:
This encoding exploits the fact that only the cyclic order of tokens matters, the exact position in the state vector
  is irrelevant.  One token (in this case the biggest token, N-1) is chosen as a fixed reference point. It will
  never move, it will always be in the last position of the vector. The operators that normally would move it
  are written so that they do the usual reversal, as required, but then also do a cyclic shift to get the
  reference token to the end of the vector.
There is now a unique goal state, and cyclic variations of a state cannot be generated, whereas in the "basic"
  encoding there are N different versions of the same state, so the state space is N times bigger than it needs
  to be.

An optimization that is normally done, but which is not done here for pedagogical reasons, is that the state vector
  does not actually have to store the reference token because it is always in the last position.
  If there are N tokens, one would make the state vector be length N-1 and drop the final position from the
  LHS and RHS of each rule.

The command line options for genTopSpinCompact are the same for genTopSpinBasic.


REFERENCES

http://www.jaapsch.net/puzzles/topspin.htm

T. Chen, S. Skiena, Sorting with fixed-length reversals, Discrete Applied Mathematics 71 (1–3) (1996) 269–295.

