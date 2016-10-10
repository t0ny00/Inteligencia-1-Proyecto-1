/*
 * Generates PSVN for the Towers of Hanoi with P pegs and D disks.
 * Uses the following encoding of the puzzle:
 *   For each disk there will be P binary state variables indicating which peg the disk is on (if disk d
 *   is on peg i, the ith state variable for d will be 1 and the others will be 0).
 *   The variables for the smallest disk are first, then the variables for the second smallest disk, etc.
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


int main(int argc, char *argv[])
{
    int P, D; // the number of pegs and disks, respectively
    int seed, mincost, maxcost, range, cost;
    bool printcost;

/******* EXTRACT COMMAND LINE ARGUMENTS ************/

    if ( (argc < 3) || (argc == 5) || (argc > 6) ) {
      cerr << "You must provide 2, 3, or 5 integers on the command line." << endl;
      cerr << "The first integer is the number of pegs (3 or more)." << endl;
      cerr << "The next integer is the number of disks (2 or more)." << endl;
      cerr << "If there are no other integers, operator costs will all be 1." << endl;
      cerr << "If there is one other integer, operator costs will all be that value." << endl;
      cerr << "If there are three additional integers, operator costs will be generated at random, and" << endl;
      cerr << "these three integers are: the minimum cost, the maximum cost, and the random number seed." << endl;
      exit(0);
    }

    if( (!sscanf( argv[1], "%d", &P )) 
          || P < 3 ) {
        cerr << "bad number of pegs: " << argv[1] << endl;
        exit( -1 );
    }
    if( (!sscanf( argv[2], "%d", &D )) 
          || D < 2 ) {
        cerr << "bad number of disks: " << argv[2] << endl;
        exit( -1 );
    }
    if (argc == 3) {
        mincost = maxcost = 1;
    } else if (argc == 4) { // uniform costs of a specified value
        if( (!sscanf( argv[3], "%d", &mincost )) 
              || mincost < 0 ) {
            cerr << "bad operator cost: " << argv[3] << endl;
            exit( -1 );
        }
        maxcost = mincost;
    } else {
        assert(argc==6);  // randomly generated costs
        if( (!sscanf( argv[3], "%d", &mincost )) 
              || mincost < 0 ) {
            cerr << "bad minimum operator cost: " << argv[3] << endl;
            exit( -1 );
        }
        if( (!sscanf( argv[4], "%d", &maxcost )) 
              || maxcost < 0 ) {
            cerr << "bad maximum operator cost: " << argv[4] << endl;
            exit( -1 );
        }
        if( ( mincost > maxcost )) {
            cerr << "minimum cost must be less than maximum cost" << endl;
            exit( -1 );
        }
        if( (!sscanf( argv[5], "%d", &seed )) 
              || seed < 2 ) {
            cerr << "bad random seed (must be 2 or larger): " << argv[5] << endl;
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


    cout << "# This file was created by genHanoi.cpp with the following command line parameters:\n#";
    for (int i=1; i<argc; ++i) {
	cout << "  " << argv[i] ;
    }
    cout << "\n\n# number of state variables\n";
    printf(" %d\n",P*D);


    cout << "\n# All state variables are binary.\n";
    for (int i=0;i<(P*D);i++)
        cout << "2 ";

    cout << "\n\n";

    for (int dmove=1; dmove<=D; ++dmove) 
    {
    for (int pfrom=1; pfrom<=P; ++pfrom)
    {
    for (int pto=1; pto<=P; ++pto)    // create the rule for moving disk dmove from peg pfrom to peg pto
    {
	if (pfrom==pto) { continue; } // the pegs involved must be different

/* LHS */

        for (int dsmaller=1; dsmaller<dmove; ++dsmaller)    // the smaller disks must not be on the pegs
        {
            for(int i=1; i<=P; ++i)    
            {
               if ( (i==pfrom) || (i==pto) ) { cout << " 0"; }
	       else { cout << " -"; }
            }
        }

        for (int i=1; i<=P; ++i)      // the disk being moved must be on peg pfrom (and not on peg pto)
        {
           if ( (i==pfrom) ) { cout << " 1"; }
           else if ( (i==pto) ) { cout << " *0"; }
	        else { cout << " -"; }
        }

        for (int dlarger=dmove+1; dlarger<=D; ++dlarger)    // the larger disks don't matter
        {
            for (int i=1; i<=P; ++i)    { cout << " -"; }
        }

        cout << " =>" ;

/* RHS */

        for (int dsmaller=1; dsmaller<dmove; ++dsmaller)    // exactly the same as LHS
        {
            for (int i=1; i<=P; ++i)    
            {
               if ( (i==pfrom) || (i==pto) ) { cout << " 0"; }
	       else { cout << " -"; }
            }
        }

        for (int i=1; i<=P; ++i)      // the disk being moved goes onto peg pto (and not onto peg pfrom)
        {
           if ( (i==pto) ) { cout << " 1"; }
           else if ( (i==pfrom) ) { cout << " *0"; }
                else { cout << " -"; }

        }

        for (int dlarger=dmove+1; dlarger<=D; ++dlarger)    // the larger disks don't matter
        {
            for (int i=1; i<=P; ++i) { cout << " -"; }
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
        for (int j=2;j<=P;++j)  { cout << " 0"; }
    } 
    cout << endl ;
    exit(0);
}
