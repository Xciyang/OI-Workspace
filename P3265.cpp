#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m, ans, cnt, bases[501];
long double z[501][501];
struct DATA {
	int cost, id;
	bool operator<(const DATA &d2) const {
		return cost < d2.cost;
	}
} datas[501];
long double absld(long double a) {
	return a < 0 ? -a : a;
}
int main() {
	cin >> n >> m;
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= m; j++) cin >> z[i][j];
	for(int i= 1; i <= n; i++) cin >> datas[i].cost, datas[i].id= i;
	sort(datas + 1, datas + n + 1);
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) {
			if(absld(z[datas[i].id][j]) > 1e-6) {
				if(!bases[j]) {
					bases[j]= datas[i].id;
					++cnt, ans+= datas[i].cost;
					break;
				}
				else {
					long double tmpp= z[datas[i].id][j] / z[bases[j]][j];
					for(int k= j + 1; k <= m; k++) z[datas[i].id][k]-= z[bases[j]][k] * tmpp;
				}
			}
		}
	}
	cout << cnt << ' ' << ans << endl;
	return 0;
}