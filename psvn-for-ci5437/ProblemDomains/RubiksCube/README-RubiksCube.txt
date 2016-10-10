DESCRIPTION
Rubik's Cube is a well-known puzzle. The standard version is 3x3x3 and consists of 27 1x1x1 cubes called cubies.
A move consists of a quarter-turn of one of the faces in either direction (clockwise or counterclockwise).
A 180 degree turn of a face is also considered a single move in our encoding of the puzzle.

The "sticker" encoding used here for both the 3x3x3 and 2x2x2 puzzle is NOT the same as the encodings
used by Rich Korf and others.

The "sticker" encoding for the 3x3x3 cube works as follows. The encoding for the 2x2x2 cube is analogous.
The cube has 6 faces, which we refer to as U (upper), F (front), R (right), B (back), L (left),
and D ("down", the face opposite U).
Each face has 9 positions on it, but the middle position never changes, so we have 8 state variables per face.
There are therefore 48 variables in this encoding.
The value of a variable tells what colour of sticker is currently in that position.

The first letter in a variable's name tells you which face it on.
If the variable represents an edge location, the name will have one additional letter saying which face it is
  adjacent to.  For example, the states variables FU, FR, FD, and FL are the edge locations on the front face:
  FU is the edge location on the front face that is adjacent to face U, FR is the edge location on the front
  face adjacent to face R, etc.
If the variable represents a corner location, it will have three letters in its name: the first one says which
  face it is on, the last two say which faces it is adjacent to.  For example, FUR is the upper-right corner of the
  front.
A useful side effect of this naming convention is that the name of a variable directly indicates which moves affect
  that variable: for example, variable FUR is affected by moves of face F, U, and R.

There are three moves for each face: a 180 degree twist, and 90 degree twists in either direction (clockwise (CW) or
  counterclockwise (CCW)).  "Clockwise" and "Counterclockwise" depend on ones frame of reference; the frame
  of reference used for naming the directions in these files may not be the most intuitive one for you.


KEY PROPERTIES
The maximum number of moves needed to solve the 3x3x3 cube is 20. See http://www.cube20.org/.
That website also lists the exact number of reachable states at each distance up to 15.

Operators involving opposite faces commute, and it is never optimal to move the same face twice in a row.
These facts have been used manually to reduce the asymptotic branching factor to approximately 13.34847.
They will be discovered automatically by psvn2c's move pruning mechanism. Note that this sort of move pruning
is not, in general, safe to do in conjunction with A* or other search algorithms that do duplicate detection.

The number of distinct states at each depth for the 2x2x2 Cube is:
1 states at distance 0
18 states at distance 1
243 states at distance 2
2874 states at distance 3
28000 states at distance 4
205416 states at distance 5
1168516 states at distance 6
5402628 states at distance 7
20776176 states at distance 8
45391616 states at distance 9
15139616 states at distance 10
64736 states at distance 11
88179840 states in total.



REFERENCE
Richard E. Korf (1997), Finding Optimal Solutions to Rubik's Cube Using Pattern Databases. AAAI.

