#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
int tmp[21][21], firstans[21][21], n, kind[16], ok;
int lefts[16][16], ups[16][16];
void init() {
	for(int i= 0; i < 16; i++)
		for(int j= 0; j < 16; j++) {
			if(((i >> 3) ^ (j >> 2)) & 1) lefts[i][j]= 1;
			if(((i >> 1) ^ (j >> 0)) & 1) ups[i][j]= 1;
		}
	for(int i= 1; i <= n; i++) tmp[0][i]= 2, tmp[i][0]= 8;
	return;
}
int dfs(int hang, int lie) {
	if(hang == n + 1) {
		if(!ok) memcpy(firstans, tmp, sizeof(firstans)), ok= 1;
		return 1;
	}
	if(lie == n + 1) return dfs(hang + 1, 1);
	int tot= 0;
	for(int i= 0; i < 16; i++) {
		if(lefts[tmp[hang][lie - 1]][i] && ups[tmp[hang - 1][lie]][i]) {
			if(hang == n && ups[i][1] == 0) continue;
			if(lie == n && lefts[i][4] == 0) continue;
			if(kind[i]) --kind[i], tmp[hang][lie]= i, tot+= dfs(hang, lie + 1), ++kind[i];
		}
	}
	return tot;
}
int main() {
	cin >> n;
	for(int i= 0; i < 16; i++) cin >> kind[i];
	init();
	if(ok= dfs(1, 1)){
		cout << ok << endl;
		for(int i= 1; i <= n; i++) {
			for(int j= 1; j <= n; j++) cout << firstans[i][j] << ' ';
			cout << endl;
		}
        return 0;
	}
	cout << "No answer!" << endl;
	return 0;
}

/*
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int tmp[21][21], firstans[21][21], n, nn= (1 << 4) - 1, kind[16], ok;
int dfs(int hang, int lie) {
	if(hang == n + 1) {
		if(!ok) memcpy(firstans, tmp, sizeof(firstans)), ok= 1;
		return 1;
	}
	if(lie == n + 1) return dfs(hang + 1, 1);
	int k= nn, tot= 0;
	if(hang == 1 || (2 & tmp[hang - 1][lie])) k^= 1;
	if(lie == 1 || (8 & tmp[hang][lie - 1])) k^= 4;
	for(int i= 1; i >= (lie == n); i--) {
		k^= (i << 3);
		for(int j= 1; j >= (hang == n); j--) {
			k^= (j << 1);
			tmp[hang][lie]= k;
			if(kind[tmp[hang][lie]]) {
				--kind[tmp[hang][lie]];
				tot+= dfs(hang, lie + 1);
				++kind[tmp[hang][lie]];
			}
			k^= (j << 1);
		}
		k^= (i << 3);
	}
	return tot;
}
int main() {
	cin >> n;
	for(int i= 0; i < 16; i++) cin >> kind[i];
	ok= dfs(1, 1);
	if(!ok)
		cout << "No answer!" << endl;
	else {
        cout << ok << endl;
        for(int i= 1; i <= n; i++){
            for(int j= 1; j  <= n; j++){
                cout << firstans[i][j] << ' ';
            }
            cout << endl;
        }
	}
	return 0;
}

*/