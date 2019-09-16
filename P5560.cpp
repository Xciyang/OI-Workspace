#include <iostream>
#include <stdio.h>
using namespace std;
int t;
long long N;
int main() {
	cin >> t;
	while(t--) {
		cin >> N;
		if(N == 4)
			cout << 5 << endl;
		else if(N == 10)
			cout << 11 << endl;
		else
			cout << N - 1 << endl;
	}
	return 0;
}