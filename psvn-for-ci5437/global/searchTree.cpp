/*
This program computes the distance to goal (i.e. the cost of the least-cost path to the goal)
of every state from which the goal can be reached.
It does this by executing Dijkstra's algorithm backwards from the goal.
It prints on stdout each state and its distance (distance first, then the state) and, if a filename is
provided as a command line argument, it prints the state_map it builds to that file.

Copyright (C) 2013 by the PSVN Research Group, University of Alberta
*/

#include <vector>
#include "priority_queue.hpp"

struct container
{
    state_t state;
    int hist;
};

int main(int argc, char **argv) {
    
    //int bound = atoi(argv[1]);

    int d, ruleid,node_counter,depth,tmp;
    ruleid_iterator_t iter;
    container father,child;

    PriorityQueue<container> open; // used for the states we have generated but not yet expanded (the OPEN list)
    FILE *file; // the final state_map is written to this file if it is provided (command line argument)

    // add goal states
    first_goal_state(&father.state, &d);
    do {
        open.Add(0, 0, father);
    } while( next_goal_state(&father.state, &d) );

    d = 0;
    depth = 0;
    node_counter = 1;
    tmp = -1;
    father.hist = init_history;
    while( !open.Empty() && depth < 7) {
        // get current distance from goal; since operator costs are
        // non-negative this distance is monotonically increasing
        d = open.CurrentPriority();
        if ( d != tmp){
            printf("Depth: %d. N: %d \n",depth,node_counter);
            tmp = d;
            node_counter = 0;
            depth++;
        }
        
        // remove top state from priority state
        father = open.Top();
        open.Pop();

        //printf("Padre %d\n",d );
        //print_state(stdout,&father.state);
        //printf("\nHijos\n" );

        // look at al predecessors of the state
        init_bwd_iter(&iter, &father.state);
        
        while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
            if (!bwd_rule_valid_for_history(father.hist,ruleid)) continue;
            child.hist = next_bwd_history(father.hist,ruleid);
            apply_bwd_rule(ruleid, &father.state, &child.state);
            const int child_d = d + 1;
            node_counter++; 

            //print_state(stdout,&child.state);
            //printf("%d\n", child.hist);
            //printf("\n");

            open.Add(child_d, child_d, child);
            
        }
    }
    

    
    return 0;
}

