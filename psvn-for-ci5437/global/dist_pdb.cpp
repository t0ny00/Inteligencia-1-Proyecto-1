#include <vector>
#include "priority_queue.hpp"

int main(int argc, char **argv) {
    // read args
    if( argc < 2 ) {
        printf("Usage: %s <pdb>\n", argv[0]);
        exit(-1);
    }
    const char *pdb_name = argv[1];

    // open pdb
    char pdb_fname[1024], abst_fname[1024];
    strcpy(pdb_fname, pdb_name);
    strcat(pdb_fname, ".pdb");
    strcpy(abst_fname, pdb_name);
    strcat(abst_fname, ".abst");
    printf("reading pdb into memory: abst=%s", abst_fname);
    abstraction_t *abst = read_abstraction_from_file(abst_fname);
    FILE *pdb_file = fopen(pdb_fname, "r");
    state_map_t *pdb = read_state_map(pdb_file);
    fclose(pdb_file);

    state_t state, child;   // NOTE: "child" will be a predecessor of state, not a successor
    int d, ruleid;
    ruleid_iterator_t iter;

    PriorityQueue<state_t> open; // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated

    // add goal states
    first_goal_state(&state, &d);
    do {
        state_map_add(map, &state, 0);
        open.Add(0, 0, state);
    } while( next_goal_state(&state, &d) );

    d = 0;
    while( !open.Empty() ) {
        // get current distance from goal; since operator costs are
        // non-negative this distance is monotonically increasing
        d = open.CurrentPriority();

        // remove top state from priority state
        state = open.Top();
        open.Pop();
        
        // check if we already expanded this state.
        // (entries on the open list are not deleted if a cheaper path to a state is found)
        const int *best_dist = state_map_get(map, &state);
        assert(best_dist != NULL);
        if( *best_dist < d ) continue;

        // compute PDB value for state
        state_t abst_state;
        abstract_state(abst, &state, &abst_state);
        const int *pdb_value = state_map_get(pdb, &abst_state);
        assert(pdb_value != 0);
        int value = *pdb_value;
        
        // print the distance then the state
        printf("%d  ",d);
        print_state(stdout, &state);
        printf(" [%d  ", value);
        print_state(stdout, &abst_state);
        printf("]\n");

        // look at all predecessors of the state
        init_bwd_iter(&iter, &state);
        while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
            apply_bwd_rule(ruleid, &state, &child);
            const int child_d = d + get_bwd_rule_cost(ruleid);

            // check if either this child has not been seen yet or if
            // there is a new cheaper way to get to this child.
            const int *old_child_d = state_map_get(map, &child);
            if( (old_child_d == NULL) || (*old_child_d > child_d) ) {
                // add to open with the new distance
                state_map_add(map, &child, child_d);
                open.Add(child_d, child_d, child);
            }
        }
    }
    
    return 0;
}

