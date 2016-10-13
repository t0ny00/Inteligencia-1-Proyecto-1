#include <vector>
#include "priority_queue.hpp"
#include <time.h>
unsigned nodes_generated = 0;


struct container
{
    state_t state;
    bool goal;
};


container boundedDfsVisit(container n, unsigned d, unsigned bound, int hist){

	int ruleid,hist_child;
	ruleid_iterator_t iter;
	container child,m;

	// print_state(stdout,&n.state);
 //    printf("\n"); 

	if (d > bound){
		m.goal = false;
		return m;
	};
	if (is_goal(&n.state) == 1){ 
		n.goal = true;
		return n;
	}

	init_fwd_iter(&iter, &n.state);
        
    while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
        if (!fwd_rule_valid_for_history(hist,ruleid)) continue;
        hist_child = next_fwd_history(hist,ruleid);
        apply_fwd_rule(ruleid, &n.state, &child.state);
        nodes_generated++;
        m = boundedDfsVisit(child,++d,bound,hist_child);
        if (m.goal != false) return m;   
    }
    m.goal = false;
    return m;

}


int main(int argc, char **argv) {

	container root;
	unsigned bound = 0;
	int hist;
	
	clock_t begin = clock();

	hist = init_history;
	read_state("15 14 13 12 11 0 1 2 3 4 5 6 7 8 9 10",&root.state);
	nodes_generated++;
	while(1){
		container n = boundedDfsVisit(root,0,bound,hist);
		if (n.goal != false) break;
		bound++;
		nodes_generated = 1;
	}


	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	printf("%d\n", nodes_generated);
	printf("%d\n", bound);
	printf("%f\n", elapsed_secs);
	printf("%f\n", nodes_generated/elapsed_secs);

}