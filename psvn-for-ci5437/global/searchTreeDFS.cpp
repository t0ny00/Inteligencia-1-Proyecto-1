#include <vector>
#include "priority_queue.hpp"
#include <time.h>


void boundedDfsVisit(state_t n, int d, int bound, int hist,unsigned results[]){

	int ruleid,hist_child;
	ruleid_iterator_t iter;
	state_t child,m;


	if (d > bound){
		return ;
	};

	init_bwd_iter(&iter, &n);
	results[d]++;
   
    while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
        if (!bwd_rule_valid_for_history(hist,ruleid)) continue;
        hist_child = next_bwd_history(hist,ruleid);
        apply_bwd_rule(ruleid, &n, &child);
        boundedDfsVisit(child,d+1,bound,hist_child,results);  
    }
    return;

}


int main(int argc, char **argv) {

	state_t root;
	int bound;
	int hist,d;

	if(argc <2){
        printf("Usage: <max bound>\n");
        exit(1);
    }

    bound = atoi(argv[1]);
	unsigned results[bound+1]={0};

	hist = init_history;
	first_goal_state(&root, &d);
	
	boundedDfsVisit(root,0,bound,hist,results);
	
	for(int i=0; i <= bound ;i++){
		printf("Depth %d: %d\n",i, results[i]);
	}

	

}