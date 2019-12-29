# include <iostream>
# include <vector>
# include <string>
# include <cstring>
# include <fstream>
# include <iomanip>
using namespace std;

struct node{
	int value;
	int color; // white = 0, gray = 1, black = 2
	int pre;
};

template<class T>
void ReadList(fstream &fin, T value, vector<T> &container){
	do{
		fin >> value;
		container.push_back(value);
		fin.get();
	}while (fin.peek() != '\n');
}

void Initialize(int size, vector<vector<node> > &table){
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			table[i][j].value = 0;
			table[i][j].color = 0;
			table[i][j].pre = 0;
		}
	}
}

int main(int argc, char** argv){
	if (argc != 3) return -1;
	fstream fin(argv[1], ios::in);
	if (!fin) return -1;
	//fstream fout(argv[2], ios::out);
	//if (!fout) return -2;

	int total, num, trucks, src, dst, cap;
	string s;
	vector<int> src_warehouse, stores;
	vector<string> capacity;
	char c;
	fin >> total;
	vector<vector<node> > table(total+1, vector<node>(total+1));
	vector<vector<node> > flow(total+1, vector<node>(total+1));
	Initialize(total+1, table);
	Initialize(total+1, flow);
	ReadList(fin, num, src_warehouse);
	ReadList(fin, num, stores);
	ReadList(fin, s, capacity);

	fin >> trucks;
	for (int i = 0; i < trucks; i++){
		fin >> src >> dst >> cap;
		table[src][dst].value = cap;
	}
	for (int i = 0; i < table.size(); i++){
		for (int j = 0; j < table.size(); j++){
			cout << setw(3) << table[i][j].value; 
		}
		cout << endl;
	}
	cout << endl;	
	for (int i = 0; i < flow.size(); i++){
		for (int j = 0; j < flow.size(); j++){
			cout << setw(3) << flow[i][j].value; 
		}
		cout << endl;
	}
	return 0;
}
