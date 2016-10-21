#include <vector>
#include "priority_queue.hpp"
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define t_max  300
using namespace std;


unsigned long long nodes_generated = 0;

clock_t begin,end;
double elapsed_timer;
bool timeout = false;
double seconds,total;
time_t t1,t2;

abstraction_t *abst[3];//abstract state maps
state_map_t *pdb[3];


struct container
{
    state_t state;
    int hist;
    int cost;
    bool goal;
    int bound;
};


// Given 3 PDB for the 15 puzzle where each one represents a domain abstraction of 10 tiles
// mapping to the blank "tile" or an indistinguishable set
int heuristic(state_t state){
	
	int h = 0;
	int *pdb_value;
	
	for (int i = 0; i < 3; ++i)
	{
	    state_t abst_state;
	    abstract_state(abst[i], &state, &abst_state);
	    pdb_value = state_map_get(pdb[i], &abst_state);
	    assert(pdb_value != 0);
    	h += *pdb_value;
	}

	return h;
}



container fBoundDfS(container father, float bound,float weight){
	
	ruleid_iterator_t iter;
	container result,child;
	int ruleid;
	nodes_generated++;
	
	float f = father.cost + weight*heuristic(father.state);
	
	t2 = time(NULL);
	seconds = difftime(t2,t1);

	if (seconds > t_max || timeout) {
		exit(3);
	}

	
	if (is_goal(&father.state) == 1) {
		father.goal = true;
		return father;
	}
	if (f > bound) {
		result.goal = false;
		result.bound = f;
		return result;
	};


	int t = INT_MAX;
	init_fwd_iter(&iter, &father.state);
	while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
    	if (!fwd_rule_valid_for_history(father.hist,ruleid)) continue;
    	child.hist = next_fwd_history(father.hist,ruleid);
    	apply_fwd_rule(ruleid, &father.state, &child.state);
    	child.cost = father.cost+1;
        result = fBoundDfS(child,bound,weight);
        if (result.goal) return result;
        t = min(t,result.bound);

    }

    result.goal = false;
    result.bound = t;
    return result;
}

int wida(container root,float weight){
	root.hist = init_history;
	float bound = weight*heuristic(root.state);
	container result;
	while(true){
		result = fBoundDfS(root,bound,weight);
		if (result.goal) return result.cost;
		bound = result.bound;

	}

}




int main(int argc, char **argv) {

	if( argc < 7 ) {
        printf("Usage: %s <instances> <outfile> <pdb1> <pdb2> <pdb3> <weight>\n", argv[0]);
        exit(-1);
    }
	    
	char pdb_name[1024];
	char pdb_fname[1024], abst_fname[1024];
	FILE *pdb_file;
	
	
	for(int i = 3; i < 6; i++){

	    strcpy(pdb_name,argv[i]);
	    strcpy(pdb_fname, pdb_name);
	    strcat(pdb_fname, ".pdb");
	    strcpy(abst_fname, pdb_name);
	    strcat(abst_fname, ".abst");
	    printf("reading pdb into memory: abst=%s\n", abst_fname);
	    abst[i-3] = read_abstraction_from_file(abst_fname);
	    pdb_file = fopen(pdb_fname, "r");
	    pdb[i-3] = read_state_map(pdb_file);
	    fclose(pdb_file);
		
	}
	    

	
    char stateChar[256];
	ifstream myfile (argv[1]);
	std::string path = argv[1];
	ofstream outfile (argv[2]);
	float weight = atof(argv[6]);
	string line;
	container root;
	outfile << "grupo, algorithm, heuristic, weight,domain, instance, cost,h0, generated, time, gen_per_sec\n";

	if (myfile.is_open()){

		while ( getline (myfile,line) ){
		  	
			strncpy(stateChar, line.c_str(), sizeof(stateChar));
			stateChar[sizeof(stateChar) - 1] = 0;
			read_state(stateChar,&root.state);
			

			begin = clock();
			t1 = time(NULL);
			
			int h = weight*heuristic(root.state);
			root.cost = 0;
			int cost = wida(root,weight);

			
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
				outfile << "x, wida, PDB, ";
				outfile << weight << ", ";
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