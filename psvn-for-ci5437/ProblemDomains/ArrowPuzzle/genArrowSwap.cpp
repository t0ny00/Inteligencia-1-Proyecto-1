/*
 * Generates PSVN for the Arrow puzzle.
 * Uses the non-standard "swap" encoding of the puzzle, which has two binary state variables for 
 *      each arrow: one of them holds the arrow's current value (0 if the arrow is pointing down,
 *	1 if it is pointing up), the other one holds the opposite value.  This allows an arrow
 *	to be flipped by swapping the values of its two variables.
 * This encoding was invented by Mokhtar Khorshid.
 * Supports two cost models:
 *      -- unifom (all operators cost the same)
 *      -- random (each operator's cost is generated uniformly at random in a user-specified range)

 * Written by Shahab Jabbari Arfaee
 * Edited by Rob Holte
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <assert.h>

using namespace std;


string convertInt(int number)
{
   ostringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int main(int argc, char *argv[])
{
    int N; // the number of arrows
    int seed, mincost, maxcost, range, cost;
    bool printcost;

/******* EXTRACT COMMAND LINE ARGUMENTS ************/

    if ( (argc < 2) || (argc == 4) || (argc > 5) ) {
      cerr << "You must provide 1, 2, or 4 integers on the command line." << endl;
      cerr << "The first integer is the number of arrows." << endl;
      cerr << "If there are no other integers, operator costs will all be 1." << endl;
      cerr << "If there is one other integer, operator costs will all be that value." << endl;
      cerr << "If there are three additional integers, operator costs will be generated at random, and" << endl;
      cerr << "these three integers are: the minimum cost, the maximum cost, and the random number seed." << endl;
      exit(0);
    }

    if( (!sscanf( argv[1], "%d", &N )) 
          || N <= 0 ) {
        cerr << "bad number of arrows: " << argv[1] << endl;
        exit( -1 );
    }
    if (argc == 2) {
        mincost = maxcost = 1;
    } else if (argc == 3) { // uniform costs of a specified value
        if( (!sscanf( argv[2], "%d", &mincost )) 
              || mincost < 0 ) {
            cerr << "bad operator cost: " << argv[2] << endl;
            exit( -1 );
        }
        maxcost = mincost;
    } else {
        assert(argc==5);  // randomly generated costs
        if( (!sscanf( argv[2], "%d", &mincost )) 
              || mincost < 0 ) {
            cerr << "bad minimum operator cost: " << argv[2] << endl;
            exit( -1 );
        }
        if( (!sscanf( argv[ 3 ], "%d", &maxcost )) 
              || maxcost < 0 ) {
            cerr << "bad maximum operator cost: " << argv[3] << endl;
            exit( -1 );
        }
        if( ( mincost > maxcost )) {
            cerr << "minimum cost must be less than maximum cost" << endl;
            exit( -1 );
        }
        if( (!sscanf( argv[4], "%d", &seed )) 
              || seed < 2 ) {
            cerr << "bad random seed (must be 2 or larger): " << argv[4] << endl;
            exit( -1 );
        }
    }

    range = maxcost-mincost+1;
    if (range == 1) {     // if range==1 we have uniform costs all equal to mincost
        cost = mincost;   
    } else {
        srand(seed);   // initialize the random number generator
    }
    printcost = (range > 1) || (mincost > 1) ;
       

/******* CREATE THE PSVN FILE ************/


    cout << "# This file was created by genArrowSwap.cpp with the following command line parameters:\n#";
    for (int i=1; i<argc; ++i) {
	cout << "  " << argv[i] ;
    }
    cout << "\n\n# number of state variables\n";
    cout << convertInt(2*N) << "\n";


    cout << "\n# All state variables are binary.\n";
    for (int i=0;i<N;i++)  { cout << "2 2 "; }  // 2 variables for each arrow

    cout << "\n\n";

    for (int i=0; i<N-1;i++)    // create the rules for flipping bits i and i+1
    {
/* LHS */
        for (int j=0;j<i;j++) { cout << " - -" ; } // variables for the first i-1 arrows are irrelevant
        cout << " A B C D" ;
        for (int j = i + 2; j < N; ++j) { cout << " - -" ; } // variables for the rest of the arrows are irrelevant
        cout << " =>" ;

/* RHS */
        for (int j=0;j<i;j++) { cout << " - -" ; } // variables for the first i-1 arrows are irrelevant
        cout << " B A D C" ;
        for (int j = i + 2; j < N; ++j) { cout << " - -" ; } // variables for the rest of the arrows are irrelevant

/* label and cost */
        cout << "  LABEL Flip_" << convertInt(i+1) << "_" << convertInt(i+2);  // the arrows are numbered from 1, not 0
        if (range > 1) { cost = mincost + (rand()%range); } // set the operator cost randomly
        if (printcost) { cout << " COST " << convertInt(cost); }
        cout << endl ;
    }
    cout << "\nGOAL ";
    for (int i=0;i<N;i++)  { cout << "0 1 "; } // in the goal, all arrows point down
    cout << endl ;
    exit(0);
}
