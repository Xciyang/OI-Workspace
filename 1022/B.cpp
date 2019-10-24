#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
int q, m, k, n[55];
inline long long qpow(__int128_t a, long long b) {
	__int128_t res= 1;
	while(b) {
		if(b & 1) {
			res= res * a;
			if(res > 100000000000000000) return 100000000000000000;
		}
		a= a * a, b>>= 1;
		if(b && a > 100000000000000000) return 100000000000000000;
	}
	return res;
}
tree< long long, null_type, less< long long >, rb_tree_tag, tree_order_statistics_node_update > nd;

int main() {
	srand(time(0));
	cin >> q;
	while(q--) {
		nd.clear();
		cin >> m >> k;
		for(int i= 1; i <= k; i++) cin >> n[i];
		sort(n + 1, n + k + 1);
        for(int i= 1; i <= k; i++) {
			for(int j= 1; j <= m; j++) {
				long long res= qpow(j, n[i]);
                if(res == 100000000000000000) break;
                if(nd.order_of_key((*nd.lower_bound(res))) > m) break;
				nd.insert(res);
			}
		}
        if(nd.size() < m) {
            cout << (long long)1e17 << endl;
        } else{
		    cout << (*nd.find_by_order(m - 1)) << endl;
        }
	}
	return 0;
}
/*
1
29 4
17 12 41 23

1
100000000 5
1 2 3 4 5

*/
/*
1
5000 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

*/