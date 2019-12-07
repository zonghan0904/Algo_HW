# include <iostream>
# include <fstream>
# include <vector>
# include <ctime>

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
	fstream fout(argv[2], ios_base::out);
	if (!fout) return -1;

	int mode, crop_A, crop_V, ans;
	fin >> mode >> field_A >> crops_K;

	for (int i = 0; i < crops_K+1; i++){
		table.push_back(vector<int>(field_A+1, 0));
	}
	for (int i = 0; i < crops_K; i++){
		fin >> crop_A >> crop_V;
		A.push_back(crop_A);
		V.push_back(crop_V);
	}

//clock_t start, stop;
//start = clock(); // timer start

	ans = max_benefit(mode);

//stop = clock();  // timer stop

	fout << ans << endl;
	
//if (mode == 0) cout << "recursive mode: " << endl;
//else if (mode == 1) cout << "dynamic programming mode: " << endl;
//else if (mode == 2) cout << "memorized recursive mode: " << endl;
//cout << "max benefit: " << ans << endl;
//cout << "execution time: " << double(stop - start) / CLOCKS_PER_SEC << endl;

	return 0;
}

// ############################ implementation ############################

int recursive(int index, int area){
	if (index <= 0) return 0;			   // iterated all situations
	int noplant = recursive(index-1, area);
	if (area < A[index]) return noplant;       // remain size < current size
	else{
		int plant = V[index] + recursive(index, area-A[index]);
		return max(plant, noplant);	 // compare the result of two situations
	}
}

int dynamic_programming(int index, int area){
	for (int i = 1; i <= crops_K; i++){
		for (int j = 0; j <= field_A; j++){
			int plant, noplant = table[i-1][j];
			plant = j - A[i] >= 0 ? V[i] + table[i][j-A[i]] : 0;  // check the current crop's size is smaller than available area. 
			table[i][j] = plant > noplant ? plant : noplant;  // store the optimal result.
		}
	}
	return table[index][area];
}

int memorized(int index, int area){
	filltable(index, area);
	return table[index][area];
}

int filltable(int index, int area){
	if (index <= 0) return 0;	
	if (table[index][area] != 0) return table[index][area];	 // return the value if it has been calculated.	   
	int noplant = filltable(index-1, area);
	if (area < A[index]){
		table[index][area] = noplant;  // store the value in table.
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
		return recursive(crops_K, field_A);
	}
	else if (mode == 1){      // dp mode
		return dynamic_programming(crops_K, field_A);
	}
	else if (mode == 2){      // memorized mode
		return memorized(crops_K, field_A);
	}
	else return 0;	
}