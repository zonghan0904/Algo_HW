# include <iostream>
# include <fstream>
# include <vector>
#include <ctime>


using namespace std;

// ############################ declaration  ############################

vector<int> A(1, 0), V(1, 0);

vector<vector<int> > table;

int field_A, crops_K;

int max_benefit(int mode);

int recursive(int index, int area);

int dynamic_programming(int index, int area);

int memorized(int index, int area);

int filltable(int index, int area);

// ############################ main function ############################

int main(int argc, char** argv){
	if (argc != 3) return -1;
	fstream fin(argv[1], ios_base::in);
	if (!fin) return -1;
	//fstream fout(argv[2], ios_base::out);
	//if (!fout) return -1;

	int mode, crop_A, crop_V;
	
	fin >> mode >> field_A >> crops_K;

	for (int i = 0; i < crops_K+1; i++){
		table.push_back(vector<int>(field_A+1, 0));
	}
	
	for (int i = 0; i < crops_K; i++){
		fin >> crop_A >> crop_V;
		A.push_back(crop_A);
		V.push_back(crop_V);
	}

clock_t start, stop;

start = clock(); // timer start

	cout << max_benefit(mode) << endl;

stop = clock();  // timer stop

cout << "executed time: " << double(stop - start) / CLOCKS_PER_SEC << endl;


	return 0;
}

// ############################ implementation ############################

int recursive(int index, int area){
	if (index > crops_K) return 0;			   // iterated all situations
	int noplant = recursive(index+1, area);
	if (area < A[index]) return noplant;       // remain size < current size
	else{
		int plant = V[index] + recursive(index, area-A[index]);
		return max(plant, noplant);	 // compare the result of two situations
	}
}

int dynamic_programming(int index, int area){
	return 0;
}

int memorized(int index, int area){
	filltable(index, area);
	return table[index][area];
}

int filltable(int index, int area){
	if (index > crops_K) return 0;	
	if (table[index][area] != 0) return table[index][area];		   
	int noplant = filltable(index+1, area);
	if (area < A[index]){
		table[index][area] = noplant;
		return noplant; 
	}       
	else{
		int plant = V[index] + filltable(index, area-A[index]);
		table[index][area] = max(plant, noplant);
		return table[index][area];	 
	}	
}

int max_benefit(int mode){
	if (mode == 0){           // recursive mode
		return recursive(1, field_A);
	}
	else if (mode == 1){      // dp mode
		return dynamic_programming(1, field_A);
	}
	else if (mode == 2){      // memorized mode
		return memorized(1, field_A);
	}	
}