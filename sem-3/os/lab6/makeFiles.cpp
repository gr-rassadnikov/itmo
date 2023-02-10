#include<iostream>
#include <fstream>

using namespace std;

int main (int argc, char **argv) {
	
	int from = atoi(argv[1]);
	ofstream fout(argv[2]);
	int C = 1000000;
	for (int i= from; i<from+C;i++){
		fout << i << endl;
	}
	return 0;
}