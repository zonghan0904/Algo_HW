# include <iostream>
# include <vector>
# include <string>
# include <fstream>
# include <iomanip>
# include <queue>
# include <climits>
# include <cstdlib>
using namespace std;

//##############################  declaration  ################################

int total;
vector<vector<int> > table; 
vector<int> src_warehouse, stores;
vector<string> capacity;

template<class T>
void ReadList(fstream &fin, T value, vector<T> &container);
bool BFS(const vector<vector<int> > &rnet, vector<int> &pre, const vector<int> &node_capacity);
int Max_flow(vector<vector<int> > &rnet, int total);
void Print_table();

//############################## main function ################################ 

int main(int argc, char** argv){
	if (argc != 3) return -1;
	fstream fin(argv[1], ios::in);
	if (!fin) return -1;
	fstream fout(argv[2], ios::out);
	if (!fout) return -2;

	int num, trucks, src, dst, cap;
	string constraint;
	fin >> total;
	ReadList(fin, num, src_warehouse);
	ReadList(fin, num, stores);
	ReadList(fin, constraint, capacity);
	for (int i = 0; i < total+2; i++){
		table.push_back(vector<int> (total+2, 0));
	}
	for (int i = 0; i < src_warehouse.size(); i++) table[0][src_warehouse[i]] = INT_MAX;
	for (int i = 0; i < stores.size(); i++) table[stores[i]][total+1] = INT_MAX;
	fin >> trucks;
	for (int i = 0; i < trucks; i++){
		fin >> src >> dst >> cap;
		table[src][dst] = cap;
	}
	//Print_table();
	//cout << "maximum flow = " << Max_flow(total) << endl;
	fout << Max_flow(table, total) << endl;
	//Print_table();
	fin.close();
	fout.close();
	return 0;
}

//############################## implementation ################################

template<class T>
void ReadList(fstream &fin, T value, vector<T> &container){
	do{
		fin >> value;
		container.push_back(value);
		fin.get();
	}while (fin.peek() != '\n');
}

bool BFS(const vector<vector<int> > &rnet, vector<int> &pre, const vector<int> &node_capacity){
	pre = vector<int> (total+2, -1);
	queue<int> Q;
	Q.push(0);
	while (!Q.empty() && pre.back() == -1){
		int cur = Q.front();
		//cout << "cur = " << cur << endl;
		Q.pop();
		for (int i = 0; i < total+2; i++){
			if (i != cur && rnet[cur][i] > 0 && pre[i] == -1 && node_capacity[i] > 0){
				Q.push(i);
				pre[i] = cur;
			}
		}
	}
	if (pre.back() != -1) return true; 
	else return false;	
}

int Max_flow(vector<vector<int> > &rnet, int total){
	vector<int> node_capacity(total+2, INT_MAX);
	for (int i = 1; i <= total; i++){
		if (capacity[i-1] == "Inf") node_capacity[i] = INT_MAX;
		else node_capacity[i] = atoi(capacity[i-1].c_str());
	}
	vector<int> pre(total+2, -1);
	int aug_flow, max_flow = 0, u, v;
	while (BFS(rnet, pre, node_capacity)){
		aug_flow = INT_MAX;
		v = total+1;
		u = pre[v];
		while (v != 0){
			//cout << "u = " << u << " v = " << v << endl;
			aug_flow = min(aug_flow, rnet[u][v]);
			v = u;
			u = pre[v];
		}
		for (int i = 0; i < node_capacity.size(); i++) aug_flow = min(aug_flow, node_capacity[i]);
		v = total+1;
		u = pre[v];
		while (v != 0){
			rnet[u][v] -= (rnet[u][v] == INT_MAX ? 0 : aug_flow);
			rnet[v][u] += (rnet[u][v] == INT_MAX ? 0 : aug_flow);
			node_capacity[v] -= (node_capacity[v] == INT_MAX ? 0 : aug_flow);
			v = u;
			u = pre[v];
		}
		max_flow += aug_flow;
	}
	return max_flow;
}

void Print_table(){
	for (int i = 0; i < table.size(); i++){
		for (int j = 0; j < table.size(); j++){
			cout << setw(3) << (table[i][j] < 1000000 ? table[i][j] : -1); 
		}
		cout << endl;
	}
}

