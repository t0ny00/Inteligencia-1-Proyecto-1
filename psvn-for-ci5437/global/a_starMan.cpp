#include <vector>
#include "priority_queue.hpp"
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define t_max  600
using namespace std;


unsigned long long nodes_generated = 0;

clock_t begin,end;
double elapsed_timer;
bool timeout = false;
double seconds;

time_t t1,t2;

struct container
{
    state_t state;
    int hist;
    int cost;
};

int array[16][16] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5},
		{2,1,0,1,3,2,1,2,4,3,2,3,5,4,3,4},
		{3,2,1,0,4,3,2,1,5,4,3,2,6,5,4,3},
		{1,2,3,4,0,1,2,3,1,2,3,4,2,3,4,5},
		{2,1,2,3,1,0,1,2,2,1,2,3,3,2,3,4},
		{3,2,1,2,2,1,0,1,3,2,1,2,4,3,2,3},
		{4,3,2,1,3,2,1,0,4,3,2,1,5,4,3,2},
		{2,3,4,5,1,2,3,4,0,1,2,3,1,2,3,4},
		{3,2,3,4,2,1,2,3,1,0,1,2,2,1,2,3},
		{4,3,2,3,3,2,1,2,2,1,0,1,3,2,1,2},
		{5,4,3,2,4,3,2,1,3,2,1,0,4,3,2,1},
		{3,4,5,6,2,3,4,5,1,2,3,4,0,1,2,3},
		{4,3,4,5,3,2,3,4,2,1,2,3,1,0,1,2},
		{5,4,3,4,4,3,2,3,3,2,1,2,2,1,0,1},
		{6,5,4,3,5,4,3,2,4,3,2,1,3,2,1,0}
	};

	

int heuristic(state_t state){
	int h = 0;
	for (long unsigned int i = 0 ; i < 16; i++){
		h += array[state.vars[i]][i]; 
	}
	return h;
}

// int aStar(container init){
	
// 	/*
// 	0: Black
// 	1: Gray
// 	2: White
// 	*/
// 	container father,child;
// 	ruleid_iterator_t iter;
// 	int ruleid,h,*g;
// 	PriorityQueue<container> open;
// 	//state_map_t *map_color = new_state_map();
// 	state_map_t *map_cost = new_state_map();
// 	state_map_add(map_cost, &init.state, 0);
// 	init.hist = init_history;
// 	//state_map_add(map_color, &init.state, 1);
// 	open.Add(heuristic(init.state),heuristic(init.state),init);
// 	printf("h0:  %d\n",heuristic(init.state) );
// 	nodes_generated++;
// 	while( !open.Empty() ) {
// 		father = open.Top();
//         int a = open.CurrentPriority();
//         //printf("%d\n", a); 
//         open.Pop();
//         g = state_map_get(map_cost,&father.state);
//         if (g == NULL || father.cost <= *g){	
//         	state_map_add(map_cost, &father.state, father.cost);
//         	if (is_goal(&father.state) == 1){ 
//         		return father.cost;
//         	}
// 			init_fwd_iter(&iter, &father.state);
// 	        while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
// 	        	if (!fwd_rule_valid_for_history(father.hist,ruleid)) continue;
// 	        	child.hist = next_fwd_history(father.hist,ruleid);
// 	            apply_fwd_rule(ruleid, &father.state, &child.state);
// 	            h = heuristic(child.state);
// 	            nodes_generated++;
// 	        	// print_state(stdout,&child.state);
// 	        	// printf("    %d\n",child.cost);
	        
// 	            if (h < INT_MAX) {

// 	            	//state_map_add(map_color, &child.state, 1);
// 	            	child.cost = father.cost+1;
// 	            	open.Add(h+father.cost+1,h+father.cost+1,child);
// 	            }
// 	        }
// 	        //state_map_add(map_color, &child.state, 0);

        	        	
//     	}

// 	}
// 	return father.cost;
// }




void expand(container father ,state_map_t *map_color, state_map_t *map_cost, PriorityQueue<container> &open){

	container child;
	ruleid_iterator_t iter;
	int ruleid,h,*g;

	init_fwd_iter(&iter, &father.state);
    while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
        apply_fwd_rule(ruleid, &father.state, &child.state);
        h = heuristic(child.state);
        if (h == INT_MAX) continue;
        child.cost = father.cost+1;
    	h = heuristic(child.state);
    	const int *child_c = state_map_get(map_color, &child.state);
        if (child_c == NULL){
        	state_map_add(map_color, &child.state, 1);
        	state_map_add(map_cost, &child.state, child.cost);
        	open.Add(h+child.cost,h+child.cost,child);
        	nodes_generated++;
        } 
        else if (child.cost <= *state_map_get(map_cost, &child.state)){
        	state_map_add(map_cost, &child.state, child.cost);
        	if (*child_c == 1){
        		open.Modify(h+child.cost,h+child.cost,0,child);
        	}
        	else{
        		state_map_add(map_color, &child.state, 1);
        		open.Add(h+child.cost,h+child.cost,child);
        nodes_generated++;
        	}
        }
    	// print_state(stdout,&child.state);
    	// printf("    %d\n",child.cost);

        	//state_map_add(map_color, &child.state, 1);
        	// child.cost = father.cost+1;
        	// open.Add(h+father.cost+1,h+father.cost+1,child);
        
    }
}

int aStar(container init){
	
	/*
	0: Black
	1: Gray
	2: White
	*/
	container father,child;
	ruleid_iterator_t iter;
	int ruleid,h,*g;
	PriorityQueue<container> open;
	state_map_t *map_color = new_state_map();
	state_map_t *map_cost = new_state_map();
	state_map_add(map_cost, &init.state, 0);
	state_map_add(map_color, &init.state, 1);
	printf("h0:  %d\n",heuristic(init.state) );
	open.Add(heuristic(init.state),heuristic(init.state),init);
	nodes_generated++;
	while( !open.Empty() ) {
		father = open.Top();
        open.Pop();

    	if (is_goal(&father.state) == 1){ 
    		return father.cost;
    	}

    	expand(father,map_color, map_color, open);
    	
		// init_fwd_iter(&iter, &father.state);
  //       while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
  //           apply_fwd_rule(ruleid, &father.state, &child.state);
  //           h = heuristic(child.state);
  //       	print_state(stdout,&child.state);
  //       	printf("    %d\n",child.cost);
  //           if (h < INT_MAX) {

  //           	//state_map_add(map_color, &child.state, 1);
  //           	child.cost = father.cost+1;
  //           	open.Add(h+father.cost+1,h+father.cost+1,child);
  //           }
  //       }
        state_map_add(map_color, &child.state, 0);

        	        	
    	

	}
	return INT_MAX;
}






int main(int argc, char **argv) {

	// state_t state;
	// clock_t begin,end;
	// container a;
	// read_state("25 24 11 10 7 3 15 16 17 18 19 26 27 20 23 0 12 13 14 21 22 4 5 6 8 9 1 2", &a.state);
	// a.cost = 0;
	// begin = clock();
	// aStar(a);
	// end = clock();

	// double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	// printf("%llu\n", nodes_generated);
	// printf("Tiempo: %f\n", elapsed_secs);
	
	if( argc < 3 ) {
        printf("Usage: %s <instances> <outfile>\n", argv[0]);
        exit(-1);
    }
	    

	
	// clock_t begin,end;
	// container a;
	// read_state("14 13 15 7 11 12 9 5 6 B 2 1 4 8 10 3", &a.state);
	// a.cost = 0;
	// begin = clock();
	// int g = ida(a);
	// end = clock();

	// double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	// printf("costo:  %d\n", g);
	// printf("%llu\n", nodes_generated);
	// printf("Tiempo: %f\n", elapsed_secs);
	// printf("Tiempo2: %f\n", total);
	
    char stateChar[256];
	ifstream myfile (argv[1]);
	std::string path = argv[1];
	ofstream outfile (argv[2]);
	string line;
	container root;
	outfile << "grupo, algorithm, domain, instance, cost,h0, generated, time, gen_per_sec\n";

	if (myfile.is_open()){

		while ( getline (myfile,line) ){
		  	
			strncpy(stateChar, line.c_str(), sizeof(stateChar));
			stateChar[sizeof(stateChar) - 1] = 0;
			read_state(stateChar,&root.state);
			
			
			// print_state(stdout,&root.state);
			// printf("\n%d\n", nodes_generated);

			begin = clock();
			int h = heuristic(root.state);
			root.cost = 0;
			int cost = aStar(root);
			//t1 = time(NULL);

			
			// if(seconds > t_max || timeout){
			// 	timeout = true;
			// 	break;
			// }
			
			end = clock();

			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			
			printf("Estado: ");
			print_state(stdout,&root.state);
			if (!timeout){
				printf("\nNodos generados: %llu\n", nodes_generated);
				printf("Costo: %d\n", cost);
				printf("h0: %d\n", h);
				printf("Tiempo: %f\n", elapsed_secs);
				printf("Nodos/seg: %f\n", nodes_generated/elapsed_secs);
				printf("==================\n");
				outfile << "x, dfid, ";
				outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
				outfile << "'" << stateChar << "', ";
				outfile << cost << ", ";
				outfile << h << ", ";
				outfile << nodes_generated << ", ";
				outfile << elapsed_secs << ", ";
				outfile << nodes_generated/elapsed_secs << endl;
			}
			else {
				printf("\nNodos generados: na\n");
				printf("Costo: na\n");
				printf("h0: %d\n", h);
				printf("Tiempo: na\n");
				printf("Nodos/seg: na\n");
				printf("==================\n");
				outfile << "x, dfid, ";
				outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
				outfile << "'" << stateChar << "', ";
				outfile << "na,";
				outfile << h << ", "; 
				outfile << "na, na, na "<< endl;
				timeout = false; 
			}
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