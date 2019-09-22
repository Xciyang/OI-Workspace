#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int h, w, A, B, tmps[1005][1005], cnt[1005], tmpx, lasta, besta;
const double BeginT= 1e7, EndT= 1e-1, ChangeT= 0.9;
void SA() {
	int x, delt, y, z;
	for(double T= BeginT; T > EndT; T*= ChangeT) {
		x= rand() % h + 1, y= rand() % w + 1, z= rand() % w + 1;
		while(min(cnt[y], h - cnt[y]) == B) y= rand() % w + 1;
		while(tmps[x][y] == tmps[x][z]) z= rand() % w + 1;
		tmpx= lasta - (min(cnt[y], h - cnt[y]) == B) - (min(cnt[z], h - cnt[z]) == B);
		cnt[y]+= (tmps[x][z] - tmps[x][y]), cnt[z]+= (tmps[x][y] - tmps[x][z]);
		tmpx= tmpx + (min(cnt[y], h - cnt[y]) == B) + (min(cnt[z], h - cnt[z]) == B);
		if(tmpx == w) {
			swap(tmps[x][y], tmps[x][z]);
			for(int i= 1; i <= h; i++) {
				for(int j= 1; j <= w; j++) cout << tmps[i][j];
				cout << endl;
			}
			exit(0);
		}
		delt= tmpx - besta;
		if(delt > 0)
			lasta= besta= tmpx, swap(tmps[x][y], tmps[x][z]);
		else if(exp(delt / T) < (double)rand() / RAND_MAX)
			cnt[y]-= (tmps[x][z] - tmps[x][y]), cnt[z]-= (tmps[x][y] - tmps[x][z]);
		else
			lasta= tmpx, swap(tmps[x][y], tmps[x][z]);
	}
	return;
}
int main() {
	srand(time(0));
	cin >> h >> w >> A >> B;
    // h= 100, w= 100, A = 30, B= 30;
	if(!A) {
		if(!B) {
			for(int i= 1; i <= h; i++) {
				for(int j= 1; j <= w; j++) cout << 0;
				cout << endl;
			}
		}
		else {
			for(int i= 1; i <= h; i++) {
				for(int j= 1; j <= w; j++) cout << (i <= B ? '1' : '0');
				cout << endl;
			}
		}
		return 0;
	}
	if(!B) {
		for(int i= 1; i <= h; i++) {
			for(int j= 1; j <= w; j++) cout << (j <= A ? '1' : '0');
			cout << endl;
		}
		return 0;
	}
	for(int i= 1; i <= h; i++)
		for(int j= 1; j <= A; j++) tmps[i][j]= 1, ++cnt[j];
	for(int i= 1; i <= w; i++) lasta+= (min(cnt[i], h - cnt[i]) == B);
	if(lasta == h) {
		for(int i= 1; i <= h; i++) {
			for(int j= 1; j <= w; j++) cout << tmps[i][j];
			cout << endl;
		}
		return 0;
	}
    SA();
    double ck= clock() / CLOCKS_PER_SEC;
	while((double)clock() / CLOCKS_PER_SEC < 2.0 - ck) SA();
	cout << -1 << endl;
	return 0;
}