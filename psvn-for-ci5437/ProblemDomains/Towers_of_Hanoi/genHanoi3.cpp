/*
 * Generates PSVN for the Towers of Hanoi with 3 pegs and D disks.
 * Uses the following encoding of the puzzle, which is only efficient
 * when there are 3 pegs.
 * For each disk there will be one state variables indicating which peg
 * the disk is on (possible values are 1, 2, and 3).
 *   The variable for the smallest disk is first, then the variable for the second smallest disk, etc.
 *    
 *   For each disk d and for each pair of pegs i and j one PSVN operator is needed for moving d
 *   from the top of peg i to the top of peg j.

 * Supports two cost models:
 *	-- unifom (all operators cost the same)
 *	-- random (each operator's cost is generated uniformly at random in a user-specified range)
 * written by Rob Holte
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <assert.h>

using namespace std;

#define P 3   // P is the number of pegs, it is 3 in this generator


int main(int argc, char *argv[])
{
    int D; // the number of disks
    int seed, mincost, maxcost, range, cost;
    bool printcost;
    int pother; // the third peg (not pfrom or pto)

/******* EXTRACT COMMAND LINE ARGUMENTS ************/

    if ( (argc < 2) || (argc == 4) || (argc > 5) ) {
      cerr << "You must provide 1, 2, or 4 integers on the command line." << endl;
      cerr << "The first integer is the number of disks (2 or more)." << endl;
      cerr << "If there are no other integers, operator costs will all be 1." << endl;
      cerr << "If there is one other integer, operator costs will all be that value." << endl;
      cerr << "If there are three additional integers, operator costs will be generated at random, and" << endl;
      cerr << "these three integers are: the minimum cost, the maximum cost, and the random number seed." << endl;
      exit(0);
    }

    if( (!sscanf( argv[1], "%d", &D )) 
          || D < 2 ) {
        cerr << "bad number of disks: " << argv[1] << endl;
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
        if( (!sscanf( argv[3], "%d", &maxcost )) 
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


    cout << "# This file was created by genHanoi3.cpp with the following command line parameters:\n#";
    for (int i=1; i<argc; ++i) {
	cout << "  " << argv[i] ;
    }
    cout << "\n\n# number of state variables\n";
    printf(" %d\n",D);


    cout << "\n# All state variables are 3-valued (1...3).\n";
    for (int i=0;i<D;i++)
        cout << "3N ";

    cout << "\n\n";

    for (int dmove=1; dmove<=D; ++dmove) 
    {
    for (int pfrom=1; pfrom<=P; ++pfrom)
    {
    for (int pto=1; pto<=P; ++pto)    // create the rule for moving disk dmove from peg pfrom to peg pto
    {
	if (pfrom==pto) { continue; } // the pegs involved must be different
        pother = 6 - (pfrom+pto) ; // the identity of the peg not involved in the move
/* LHS */

        for (int dsmaller=1; dsmaller<dmove; ++dsmaller)    // the smaller disks must be on the other peg
        {
	    printf(" %d",pother);
        }

        printf(" %d",pfrom);      // the disk being moved must be on peg pfrom

        for (int dlarger=dmove+1; dlarger<=D; ++dlarger)    // the larger disks don't matter
        {
            cout << " -";
        }

        cout << " =>" ;

/* RHS is identical to LHS except for the disk being moved */

        for (int dsmaller=1; dsmaller<dmove; ++dsmaller)    // the smaller disks must be on the other peg
        {
            printf(" %d",pother);
        }

        printf(" %d",pto);      // the disk being moved ends up on peg pto

        for (int dlarger=dmove+1; dlarger<=D; ++dlarger)    // the larger disks don't matter
        {
            cout << " -";
        }


        printf("  LABEL Disk%d_From%d_To%d",dmove,pfrom,pto);
        if (range > 1) { cost = mincost + (rand()%range); } // set the operator cost randomly
        if (printcost) { printf(" COST %d",cost); }
        cout << endl ;
    
    } // end pto loop
    } // end pfrom loop
    } // end dmove loop
    
    cout << "\nGOAL";
    for (int i=1;i<=D;++i)
    { 
        cout << " 1";  // in the goal all the disks are on the first peg
    } 
    cout << endl ;
    exit(0);
}
