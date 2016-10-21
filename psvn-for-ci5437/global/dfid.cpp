#include <vector>
#include "priority_queue.hpp"
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#define t_max  600 //600 seconds -> 10 min runtime
using namespace std;


unsigned long long nodes_generated = 0;
bool timeout = false;

//Global variables to time 10 minutes from within the code
time_t t1,t2;
double seconds;

struct container
{
    state_t state;
    int cost;
};


container boundedDfsVisit(container n, unsigned d, unsigned bound, int hist){

	int ruleid,hist_child;
	ruleid_iterator_t iter;
	container child,m;
	

	t2 = time(NULL);
	seconds = difftime(t2,t1);
	if (seconds > t_max || timeout) { //Check if 10 minutes have passed since the start of the search
		timeout = true;
		return m;
	}

	if (d > bound){
		return m;
	};
	if (is_goal(&n.state)){ 
		n.cost = d;
		return n;
	}

	init_fwd_iter(&iter, &n.state);
    while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
        if (!fwd_rule_valid_for_history(hist,ruleid)) continue;
        hist_child = next_fwd_history(hist,ruleid);
        apply_fwd_rule(ruleid, &n.state, &child.state);
        nodes_generated++;
        m = boundedDfsVisit(child,d+1,bound,hist_child);

        if (is_goal(&m.state)) return m;   
    }
    return m;

}


int main(int argc, char **argv) {

	container root,n;
	unsigned bound = 0;
	int hist;
	string line;
	char stateChar[256];
	clock_t begin,end;
	

	if(argc <3){
        printf("Usage: <input file> <output file>\n");
        exit(1);
    }
	
    //Get file's name
	ifstream myfile (argv[1]);
	std::string path = argv[1];
	ofstream outfile (argv[2]);
	outfile << "grupo, algorithm, domain, instance, cost, generated, time, gen_per_sec\n";
	
	if (myfile.is_open()){

		while ( getline (myfile,line) ){
		  	
			strncpy(stateChar, line.c_str(), sizeof(stateChar));
			stateChar[sizeof(stateChar) - 1] = 0;
			hist = init_history;

			read_state(stateChar,&root.state);
			nodes_generated++;
			

			t1 = time(NULL); //Begin to count time
			begin = clock();	// Start cpu timer	

			//Main Loop
			while(1){
				n = boundedDfsVisit(root,0,bound,hist);
				if (is_goal(&n.state)) break;
				bound++;
				if(seconds > t_max || timeout) break;
			}
			end = clock(); //Take finish time of the process

			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			
			// Print Results
			printf("Estado: ");
			print_state(stdout,&root.state);
			if (!timeout){
				printf("\nNodos generados: %llu\n", nodes_generated);
				printf("Costo: %d\n", n.cost);
				printf("Tiempo: %f\n", elapsed_secs);
				printf("Nodos/seg: %f\n", nodes_generated/elapsed_secs);
				printf("==================\n");
				outfile << "x, dfid, ";
				outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
				outfile << "'" << stateChar << "', ";
				outfile << n.cost << ", ";
				outfile << nodes_generated << ", ";
				outfile << elapsed_secs << ", ";
				outfile << nodes_generated/elapsed_secs << endl;
			}
			else {
				printf("\nNodos generados: na\n");
				printf("Costo: na\n");
				printf("Tiempo: na\n");
				printf("Nodos/seg: na\n");
				printf("==================\n");
				outfile << "x, dfid, ";
				outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
				outfile << "'" << stateChar << "', ";
				outfile << "na, na, na, na "<< endl;
				timeout = false; 
			}
			nodes_generated = 0;
			n.cost = 0;
			bound = 0;
		}

		myfile.close();
		outfile.close();
	}
	else {
		cout << "No existe el archivo especificado\n";
		exit(1);
	}

	
	

}