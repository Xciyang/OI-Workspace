#include <iostream>
#include <string>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::string;

int main(void) {
	const size_t size= 1024 * 1024 * 512;
	int len= 0;
	string tmp(size, L'a');
	ofstream ofs("./a.txt");
	while(++len) {
		ofs << tmp;
		if(len % 2 == 0) {
			cout << len / 2 << 'G' << endl;
			if(getchar() == EOF) break;
		}
	}
	ofs.close();
	return 0;
}