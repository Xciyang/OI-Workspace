#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int n, m, k, t, v[4005], y[4005];
int tmpx, tmpy, tmpz;
vector < int > h[4005];
int main() {
    cin >> n >> m >> k >> t;
    for(int i= 1; i <= k; i++) {
        cin >> tmpx >> y[i] >> v[i];
        h[tmpx].push_back(i);
    }
	return 0;
}