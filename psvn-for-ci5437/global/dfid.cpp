#include <vector>
#include "priority_queue.hpp"
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#define t_max  600
using namespace std;


unsigned long long nodes_generated = 0;

clock_t beginTimer,endTimer;
double elapsed_timer;
bool timeout = false;
double seconds;

time_t t1,t2;

struct container
{
    state_t state;
    bool goal;
    int cost;
};


container boundedDfsVisit(container n, unsigned d, unsigned bound, int hist){

	int ruleid,hist_child;
	ruleid_iterator_t iter;
	container child,m;

	// endTimer = clock();
	// elapsed_timer = double(endTimer - beginTimer) / CLOCKS_PER_SEC;
	// printf("%f\n", elapsed_timer);

	t2 = time(NULL);
	seconds = difftime(t2,t1);
	// printf("%f\n",seconds );
	
	if (seconds > t_max || timeout) {
		timeout = true;
		return m;
	}

	if (d > bound){
		m.goal = false;
		return m;
	};
	if (is_goal(&n.state) == 1){ 
		n.goal = true;
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

        if (m.goal != false) return m;   
    }
    m.goal = false;
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
			
			// print_state(stdout,&root.state);
			// printf("\n%d\n", nodes_generated);

			begin = clock();
			// beginTimer = clock();
			t1 = time(NULL);

			while(1){
				n = boundedDfsVisit(root,0,bound,hist);
				if (n.goal != false) break;
				bound++;
				// endTimer = clock();
				//t2 = time(NULL);
				//seconds = difftime(t2,t1);
				//printf("%f\n",seconds );
				// elapsed_timer = double(endTimer - beginTimer) / CLOCKS_PER_SEC;
				if(seconds > t_max || timeout){
					timeout = true;
					break;
				}
			}
			end = clock();

			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			
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