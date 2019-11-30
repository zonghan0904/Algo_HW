# include <iostream>
# include <fstream>

using namespace std;

int main(int argc, char** argv){
	if (argc != 3) return -1;
	fstream fin(argv[1], ios_base::in);
	if (!fin) return -1;
	fstream fout(argv[2], ios_base::out);
	if (!fout) return -1;

	int mode, field_A, crops_K;
	fin << mode << field_A << crops_K;


	return 0;
}