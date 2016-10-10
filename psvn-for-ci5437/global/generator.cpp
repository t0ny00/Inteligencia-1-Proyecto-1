#include <iostream>
#include <vector>

using namespace std;

int valid_ruleids[10240];

void generate_state(const state_t &root, state_t &result, int bound) {
    int history = init_history;
    copy_state(&result, &root);
    for( int depth = 0; depth < bound; ++depth ) {
        int ruleid;
        ruleid_iterator_t iter;

        int index = 0;
        init_bwd_iter(&iter, &result);
        while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
            if( bwd_rule_valid_for_history(history, ruleid) == 0 ) continue;
            assert(index < 10240);
            valid_ruleids[index++] = ruleid;
        }

        if( index == 0 ) {
            break;
        } else {
            state_t child;
            int ruleid = valid_ruleids[lrand48() % index];
            apply_bwd_rule(ruleid, &result, &child);
            copy_state(&result, &child);
        }
    }
}
 
int main(int argc, const char **argv) {
    if( argc < 4 ) {
        cout << argv[0] << " <seed> <n> <depth-bound>" << endl;
        return -1;
    }
    int seed = atoi(argv[1]);
    int n = atoi(argv[2]);
    int bound = atoi(argv[3]);
    char buff[1024];

    unsigned short seed_array[3];
    seed_array[0] = seed_array[1] = seed_array[2] = seed;
    seed48(seed_array);

    int d;
    state_t goal;
    first_goal_state(&goal, &d);

    for( int i = 0; i < n; ++i ) {
        state_t state;
        generate_state(goal, state, bound);
        sprint_state(buff, 1024, &state);
        buff[strlen(buff) - 1] = '\0';
        cout << buff << endl;
    }
    return 0;
}

