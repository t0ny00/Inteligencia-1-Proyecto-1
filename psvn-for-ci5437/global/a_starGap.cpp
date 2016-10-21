/* A* algorithm with duplicate elimination and Gap heuristic for the pancake problem*/

#include <vector>
#include "priority_queue.hpp"
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define t_max  600 //600 seconds -> 10 min runtime
using namespace std;



unsigned long long nodes_generated = 0;

clock_t begin,end;


struct container
{
    state_t state;
    int hist;
    int cost;
};


/*Gap heuristic where if a pancake is 2 or more sizes different than the one next to it, is counted as
 towards the final value*/

int heuristic(state_t state){
	int h;

	h = 0;
	for (int i = 0 ; i < 28 - 1 ; i++){
		if (abs(state.vars[i] - state.vars[i+1])  > 1 ) h ++;
	}
	
	if (abs(state.vars[27] - 28) > 1) h++; // Check if the bottom pancake is the biggest one
	return h;
}


int aStar(container init){
	

	container father,child;
	ruleid_iterator_t iter;
	int ruleid,h,*g;
	PriorityQueue<container> open;

	state_map_t *map_cost = new_state_map();
	state_map_add(map_cost, &init.state, 0);
	init.hist = init_history;
	open.Add(heuristic(init.state),heuristic(init.state),init);
	nodes_generated++;
	while( !open.Empty() ) {
		father = open.Top();
        int a = open.CurrentPriority();
        open.Pop();
        g = state_map_get(map_cost,&father.state);
        if (g == NULL || father.cost <= *g){	
        	state_map_add(map_cost, &father.state, father.cost);
        	if (is_goal(&father.state) == 1){ 
        		return father.cost;
        	}
			init_fwd_iter(&iter, &father.state);
	        while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
	        	if (!fwd_rule_valid_for_history(father.hist,ruleid)) continue;
	        	child.hist = next_fwd_history(father.hist,ruleid);
	            apply_fwd_rule(ruleid, &father.state, &child.state);
	            h = heuristic(child.state);
	            nodes_generated++;
	        
	            if (h < INT_MAX) {


	            	child.cost = father.cost+1;
	            	open.Add(h+father.cost+1,h+father.cost+1,child);
	            }
	        }


        	        	
    	}

	}
	return father.cost;
}



int main(int argc, char **argv) {


	
	if( argc < 3 ) {
        printf("Usage: %s <instances> <outfile>\n", argv[0]);
        exit(-1);
    }
	    

	
    char stateChar[256];
	ifstream myfile (argv[1]);
	std::string path = argv[1];
	ofstream outfile (argv[2]);
	string line;
	container root;
	outfile << "grupo, algorithm, heuristic,domain, instance, cost,h0, generated, time, gen_per_sec\n";

	if (myfile.is_open()){

		while ( getline (myfile,line) ){
		  	
			strncpy(stateChar, line.c_str(), sizeof(stateChar));
			stateChar[sizeof(stateChar) - 1] = 0;
			read_state(stateChar,&root.state);
			
			

			begin = clock();
			int h = heuristic(root.state);
			root.cost = 0;
			int cost = aStar(root);

			
			end = clock();

			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			
			printf("Estado: ");
			print_state(stdout,&root.state);
			printf("\nNodos generados: %llu\n", nodes_generated);
			printf("Costo: %d\n", cost);
			printf("h0: %d\n", h);
			printf("Tiempo: %f\n", elapsed_secs);
			printf("Nodos/seg: %f\n", nodes_generated/elapsed_secs);
			printf("==================\n");
			outfile << "x, astar, ";
			outfile << "Gap, ";
			outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
			outfile << "'" << stateChar << "', ";
			outfile << cost << ", ";
			outfile << h << ", ";
			outfile << nodes_generated << ", ";
			outfile << elapsed_secs << ", ";
			outfile << nodes_generated/elapsed_secs << endl;
			
			nodes_generated = 0;
		}

		myfile.close();
		outfile.close();
	}
	else {
		cout << "No existe el archivo especificado\n";
		exit(1);
	}

	
	

}