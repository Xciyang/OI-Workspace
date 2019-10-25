#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;
int n, a[1000005], nowa[1000005], bestans= 0x7f7f7f7f;
const double BeginT= 10000000, EndT= 1e-1, ChangeT= 0.95;
int check() {
	int st= 1, fst= 1;
	for(int i= 2; i <= n; i++) {
		if(nowa[i] < nowa[i - 1]) break;
		++st;
	}
	for(int i= n - 1; i; i--) {
		if(nowa[i] < nowa[i + 1]) break;
		++fst;
	}
	return st + fst - 1;
}
void SA() {
	for(int i= 1; i <= n; i++) nowa[i]= a[i];
	int tmpans= 0, lastc= check();
	if(lastc < n) {
		for(double T= BeginT; T > EndT; T*= ChangeT) {
			int x= rand() % n;
			swap(nowa[x], nowa[x + 1]), ++tmpans;
			int nowc= check();
			if(nowc >= n) {
				lastc= nowc;
				break;
			}
			if(nowc > lastc || exp((nowc - lastc) / T) > (double)rand() / RAND_MAX) {
				lastc= nowc;
			}
			else {
				swap(nowa[x], nowa[x + 1]), --tmpans;
			}
		}
		if(lastc < n) tmpans= 0x7f7f7f7f;
	}
	bestans= min(bestans, tmpans);
	return;
}
int main() {
	srand(time(0));
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i];
	for(int i= 0; i < 10000; i++) SA();
	cout << bestans << endl;
	return 0;
}