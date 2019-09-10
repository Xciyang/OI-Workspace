#include <iostream>
#include <math.h>
using namespace std;
int t;
long long n;
double absl(double x) {
	return x < 0 ? -x : x;
}
int main() {
	cin >> t;
	while(t--) {
		cin >> n;
		for(long long k= 2; k <= 1e9; k+=2) {
			long long a= sqrt(k * n + 1);
			if(a * a == k * n + 1 && a % 2 == 1) {
				cout << (a - 1) / 2 * ((a - 1) / 2 + 1) << endl;
				break;
			}
		}
	}
	return 0;
}