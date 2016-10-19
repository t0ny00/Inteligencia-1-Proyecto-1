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
double seconds,total;

time_t t1,t2;








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

struct container
{
    state_t state;
    int hist;
    int cost;
    bool goal;
    int bound;
};

void split(const std::string &s, char delim, vector<int> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(atoi( item.c_str() ));
    }
}



void buildManhattan(){
	// array[16][16] = {
	// 	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	// 	{1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5},
	// 	{2,1,0,1,3,2,1,2,4,3,2,3,5,4,3,4},
	// 	{3,2,1,0,4,3,2,1,5,4,3,2,6,5,4,3},
	// 	{1,2,3,4,0,1,2,3,1,2,3,4,2,3,4,5},
	// 	{2,1,2,3,1,0,1,2,2,1,2,3,3,2,3,4},
	// 	{3,2,1,2,2,1,0,1,3,2,1,2,4,3,2,3},
	// 	{4,3,2,1,3,2,1,0,4,3,2,1,5,4,3,2},
	// 	{2,3,4,5,1,2,3,4,0,1,2,3,1,2,3,4},
	// 	{3,2,3,4,2,1,2,3,1,0,1,2,2,1,2,3},
	// 	{4,3,2,3,3,2,1,2,2,1,0,1,3,2,1,2},
	// 	{5,4,3,2,4,3,2,1,3,2,1,0,4,3,2,1},
	// 	{3,4,5,6,2,3,4,5,1,2,3,4,0,1,2,3},
	// 	{4,3,4,5,3,2,3,4,2,1,2,3,1,0,1,2},
	// 	{5,4,3,4,4,3,2,3,3,2,1,2,2,1,0,1},
	// 	{6,5,4,3,5,4,3,2,4,3,2,1,3,2,1,0}
	// };
	
	// int p,q;
	// p = 0;
	// q = 0;
	// int tmp[4][4];
	// for (int i = 0; i < 4; i++){
	// 	for (int j = 0; j < 4; j++){
	// 		for (int h = 0; h < 4; h++){
	// 			for (int k = 0; k < 4; k++){
	// 				tmp[h][k] = abs(i-h) + abs(j-k);
	// 				printf("%d,",tmp[h][k] );		
	// 			}
				
	// 			// for (int q = 0; q < 16; q++){
	// 			// 	array[p][q] = 
	// 			// }	

	// 			// for (q = 0; q < 4; q++)
	// 			// {
	// 			//     for (int t = 0; t < 4; t++)
	// 			//     {
	// 			//         array[p][q * 4 + t] = tmp[q][t];
	// 			//     }
	// 			// }
	// 			// p++;
	// 		}
	// 		printf("\n");
	// 	}
	// }
}


int heuristic(state_t state){
	int h = 0;
	for (long unsigned int i = 0 ; i < 16; i++){
		h += array[state.vars[i]][i]; 
	}
	return h;
}





container fBoundDfS(container father, int bound){
	
	ruleid_iterator_t iter;
	container result,child;
	int ruleid;
	nodes_generated++;
	
	int f = father.cost + heuristic(father.state);
	
	
	//print_state(stdout,&father.state);
	//printf("    %d    %d\n",bound,father.cost);
	
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
        result = fBoundDfS(child,bound);
        if (result.goal) return result;
        t = min(t,result.bound);

    }

    result.goal = false;
    result.bound = t;
    return result;
}

int ida(container root){
	root.hist = init_history;
	int bound = heuristic(root.state);
	container result;
	while(true){
		result = fBoundDfS(root,bound);
		if (result.goal) return result.cost;
		bound = result.bound;

	}

}




int main(int argc, char **argv) {

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
			int cost = ida(root);
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