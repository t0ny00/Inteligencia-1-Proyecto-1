/* 
 * Created by Rob Holte
 * This file generates PSVN files for (N,K)-TopSpin in the "basic" encoding.
*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <assert.h>

using namespace std;


/* GLOBAL VARIABLES */
int N; // N is the number of tokens
int K; // K is the size of the turntable
int mincost, maxcost, range;
bool printcost;

string convertInt(int number)
{
   ostringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}


void topspin_basic_rule(int r) {
    string tstr1="";
    string tstr2="";

    if (r+K <= N) { /* no wraparound */
        for (int i=0; i<r; i++)  // the first r-1 positions are "don't care" in both LHS and RHS
        {
            tstr1=tstr1+"-  ";
            tstr2=tstr2+"-  ";
        }

        for (int i=1; i<=K; i++)  // the next K positions are the ones to reverse
        {
            tstr1=tstr1+"X"+convertInt(i)+" ";  // put variables X1...XK in the LHS turnstile
            tstr2=tstr2+"X"+convertInt(K+1-i)+" ";// put variables XK...X1 in the RHS turnstile
        }
        for (int i=r+K; i<N; i++)  // the remaining positions are "don't care" in both LHS and RHS
        {
            tstr1=tstr1+"-  ";
            tstr2=tstr2+"-  ";
        }
    } else { /* wraparound */
        for (int i=(N-r)+1; i<=K; i++)  // the first positions are the LAST K-(N-r) variables
        {
            tstr1=tstr1+"X"+convertInt(i)+" ";  // put variable i in the LHS turnstile
            tstr2=tstr2+"X"+convertInt(K+1-i)+" ";// put variables in the RHS turnstile in the opposite orde
        }

        for (int i=1; i<=N-K; i++)  // the next N-K positions are the don't cares
        {
            tstr1=tstr1+"-  ";
            tstr2=tstr2+"-  ";

        }
        for (int i=1; i<=N-r; i++)  // the remaining positions are the first (N-r) variables
        {
            tstr1=tstr1+"X"+convertInt(i)+" ";  // put variable i in the LHS turnstile
            tstr2=tstr2+"X"+convertInt(K+1-i)+" ";// put variables in the RHS turnstile in the opposite order

        }

    }

    cout << tstr1 << "=> " << tstr2 << "LABEL RevAt" << convertInt(r);

    int cost=mincost;
    if (range > 1) { cost = mincost + (rand()%range); } // set the operator cost randomly
    if (printcost) { cout << " COST " << convertInt(cost); }
    cout << endl ;
}



int main(int argc, char *argv[])
{
    int seed;

/******* EXTRACT COMMAND LINE ARGUMENTS ************/

    if ( (argc < 3) || (argc == 5) || (argc > 7) ) {
      cerr << "You must provide 2, 3, or 5 integers on the command line." << endl;
      cerr << "The first integer is the number of tokens. The second is the size of the turntable." << endl;
      cerr << "If there are no other integers, operator costs will all be 1." << endl;
      cerr << "If there is one other integer, operator costs will all be that value." << endl;
      cerr << "If there are three additional integers, operator costs will be generated at random, and" << endl;
      cerr << "these three integers are: the minimum cost, the maximum cost, and the random number seed." << endl;
      exit( -1 );
    }

    if( (!sscanf( argv[1], "%d", &N ))
          || N <= 1 ) {
        cerr << "bad number of tokens (must be at least 2): " << argv[1] << endl;
        exit( -1 );
    }
    if( (!sscanf( argv[2], "%d", &K ))
          || (K <= 1)
          || (K > N-1) ) {
        cerr << "bad turntable size (must be at least 2, and cannot be more than the number of tokens minus 1): " << argv[2] << endl;
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
    } else {              // argc==6
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
    if (range != 1) { srand(seed); }  // initialize the random number generator
    printcost = (range > 1) || (mincost > 1) ;


/******* CREATE THE PSVN FILE ************/

    cout << "# This file was created by genTopSpinBasic.cpp with the following command line parameters:\n#";
    for (int i=1; i<argc; ++i) {
        cout << "  " << argv[i] ;
    }
    cout << "\n\n# number of state variables = the number of tokens" << endl;
    cout << convertInt(N) << endl;

    string Nstring = convertInt(N);
    cout << "\n# All state variables have "  << Nstring << " possible values."<< endl;
    for (int i=0;i<N;i++)  { cout << " " << Nstring; }

    cout << "\n\n";

    for (int r=0; r<N; r++)  // create the rule to reverse K positions starting in position r.
    {
        topspin_basic_rule(r);
    }

    cout << endl;

/* In this encoding there are N different goal states, all the cyclic permutations of 0...(N-1) */    
    for (int r=0; r<N; r++)  // r will be the token in the first vector position
    { 
        cout << "GOAL " ;
        for (int i=0;i<N;i++)
        {
            cout << convertInt((r+i)%N) << " ";
        }
        cout << endl;
    }

    return (EXIT_SUCCESS);
}


