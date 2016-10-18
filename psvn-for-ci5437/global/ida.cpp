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

clock_t beginTimer,endTimer;
double elapsed_timer;
bool timeout = false;
double seconds;

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


int heuristic(state_t state){
	int h,tmp;
	vector<int> state_vector;
	char state_s[1024];
	sprint_state(state_s,1024, &state);
	split(state_s,' ',state_vector);
	int* state_array = &state_vector[0];
	h = 0;
	for (unsigned int i = 0 ; i < state_vector.size() - 1 ; i++){
		tmp = abs(state_array[i] - state_array[i+1]);
		if (tmp  > 1 ) {h ++;
			//printf("%d + %d \n", state_array[i],state_array[i+1]);
		}
	}
	tmp = abs(state_array[state_vector.size()-1] - (int)state_vector.size());
	if (tmp > 1) h++;
		//exit(1);	
	return h;
}

void buildManhattan(int array[][16]){
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
	// 			}
	// 		printf("%d %d %d %d\n",tmp[h][0],tmp[h][1],tmp[h][2],tmp[h][3] );		
				
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


int heuristic2(state_t state){
	int h,tmp;
	vector<int> state_vector;
	char state_s[1024];
	sprint_state(state_s,1024, &state);
	split(state_s,' ',state_vector);
	int* state_array = &state_vector[0];
	h = 0;
	for (unsigned int i = 0 ; i < state_vector.size(); i++){
		//printf("%d: %d\n", state_array[i], array[state_array[i]][i]);
		h += array[state_array[i]][i]; 
	}
		//printf("===\n");
	return h;
}

// void expand(container father ,state_map_t *map_color, state_map_t *map_cost, PriorityQueue<container> &open){

// 	container child;
// 	ruleid_iterator_t iter;
// 	int ruleid,h,*g;

// 	init_fwd_iter(&iter, &father.state);
//     while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
//         apply_fwd_rule(ruleid, &father.state, &child.state);
//         h = heuristic(child.state);
//         if (h == INT_MAX) continue;
//         child.cost = father.cost+1;
//     	h = heuristic(child.state);
//     	const int *child_c = state_map_get(map_color, &child.state);
//         if (child_c == NULL){
//         	state_map_add(map_color, &child.state, 1);
//         	state_map_add(map_cost, &child.state, child.cost);
//         	open.Add(h+child.cost,h+child.cost,child);
//         	nodes_generated++;
//         } 
//         else if (child.cost <= *state_map_get(map_cost, &child.state)){
//         	state_map_add(map_cost, &child.state, child.cost);
//         	if (*child_c == 1){
//         		open.Modify(h+child.cost,h+child.cost,0,child);
//         	}
//         	else{
//         		state_map_add(map_color, &child.state, 1);
//         		open.Add(h+child.cost,h+child.cost,child);
//         nodes_generated++;
//         	}
//         }
//     	// print_state(stdout,&child.state);
//     	// printf("    %d\n",child.cost);

//         	//state_map_add(map_color, &child.state, 1);
//         	// child.cost = father.cost+1;
//         	// open.Add(h+father.cost+1,h+father.cost+1,child);
        
//     }
// }



container fBoundDfS(container father, int bound){
	
	ruleid_iterator_t iter;
	container result,child;
	int ruleid;
	nodes_generated++;
	int f = father.cost + heuristic2(father.state) +1;
	print_state(stdout,&father.state);
	printf("    %d    %d\n",bound,father.cost);
	
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
	int bound = heuristic2(root.state);
	container result;
	printf("%d\n", bound);
	while(true){
		result = fBoundDfS(root,bound);
		if (result.goal) return result.cost;
		bound = result.bound;

	}

}




int main(int argc, char **argv) {

	


	state_t state;
	clock_t begin,end;
	container a;
	read_state("6 11 1 4 2 5 14 13 7 12 8 10 15 B 3 9", &a.state);
	a.cost = 0;
	begin = clock();
	int g = ida(a);
	end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	printf("costo:  %d\n", g);
	printf("%llu\n", nodes_generated);
	printf("Tiempo: %f\n", elapsed_secs);
	
	// container root,n;
	// unsigned bound = 0;
	// int hist;
	// string line;
	// char stateChar[256];
	// clock_t begin,end;
	

	// if(argc <3){
 //        printf("Usage: <input file> <output file>\n");
 //        exit(1);
 //    }
	
    
	// ifstream myfile (argv[1]);
	// std::string path = argv[1];
	// ofstream outfile (argv[2]);
	// outfile << "grupo, algorithm, domain, instance, cost, generated, time, gen_per_sec\n";
	
	// if (myfile.is_open()){

	// 	while ( getline (myfile,line) ){
		  	
	// 		strncpy(stateChar, line.c_str(), sizeof(stateChar));
	// 		stateChar[sizeof(stateChar) - 1] = 0;
	// 		hist = init_history;

	// 		read_state(stateChar,&root.state);
	// 		nodes_generated++;
			
	// 		// print_state(stdout,&root.state);
	// 		// printf("\n%d\n", nodes_generated);

	// 		begin = clock();
	// 		// beginTimer = clock();
	// 		t1 = time(NULL);

	// 		while(1){
	// 			n = boundedDfsVisit(root,0,bound,hist);
	// 			if (n.goal != false) break;
	// 			bound++;
	// 			// endTimer = clock();
	// 			//t2 = time(NULL);
	// 			//seconds = difftime(t2,t1);
	// 			//printf("%f\n",seconds );
	// 			// elapsed_timer = double(endTimer - beginTimer) / CLOCKS_PER_SEC;
	// 			if(seconds > t_max || timeout){
	// 				timeout = true;
	// 				break;
	// 			}
	// 		}
	// 		end = clock();

	// 		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			
	// 		printf("Estado: ");
	// 		print_state(stdout,&root.state);
	// 		if (!timeout){
	// 			printf("\nNodos generados: %llu\n", nodes_generated);
	// 			printf("Costo: %d\n", n.cost);
	// 			printf("Tiempo: %f\n", elapsed_secs);
	// 			printf("Nodos/seg: %f\n", nodes_generated/elapsed_secs);
	// 			printf("==================\n");
	// 			outfile << "x, dfid, ";
	// 			outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
	// 			outfile << "'" << stateChar << "', ";
	// 			outfile << n.cost << ", ";
	// 			outfile << nodes_generated << ", ";
	// 			outfile << elapsed_secs << ", ";
	// 			outfile << nodes_generated/elapsed_secs << endl;
	// 		}
	// 		else {
	// 			printf("\nNodos generados: na\n");
	// 			printf("Costo: na\n");
	// 			printf("Tiempo: na\n");
	// 			printf("Nodos/seg: na\n");
	// 			printf("==================\n");
	// 			outfile << "x, dfid, ";
	// 			outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
	// 			outfile << "'" << stateChar << "', ";
	// 			outfile << "na, na, na, na "<< endl;
	// 			timeout = false; 
	// 		}
	// 		nodes_generated = 0;
	// 		n.cost = 0;
	// 		bound = 0;
	// 	}

	// 	myfile.close();
	// 	outfile.close();
	// }
	// else {
	// 	cout << "No existe el archivo especificado\n";
	// 	exit(1);
	// }

	
	

}