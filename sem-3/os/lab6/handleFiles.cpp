#include<iostream>
#include <fstream>

using namespace std;

int main (int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout;
	fout.open(argv[1], ios::app);

	int C = 1000000;
	for (int i= 0; i<C;i++){
		int in;
		fin >> in;
		fout << 2*in << endl;
	}
	return 0;
}