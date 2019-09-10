
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int M= 1000001;

int n, m, k, T, a[M], b[55][55], w[55], len, q[55], p[55];
char c[55], d[55];

void ad() {
	w[1]+= 1;
	for(int i= 1; i <= len; i++) {
		w[i + 1]+= w[i] / 10;
		w[i]%= 10;
	}
	if(w[len + 1]) len+= 1;
}

bool add() {
	for(int i= len; i >= 1; i--) {
		if(p[i] > -1) {
			if(w[i] == p[i]) continue;
			if(w[i] > p[i]) {
				int P= i + 1;
				while(p[P] > -1) P++;
				w[P]+= 1, w[i]= p[i];
				if(P > len) return 0;
			}
			else
				w[i]= p[i];
			for(int j= i - 1; j >= 1; j--) {
				if(p[j] != -1)
					w[j]= p[j];
				else
					w[j]= 0;
			}
			int k= i + 1;
			while(w[k] > 10) {
				w[k + 1]++;
				w[k]%= 10;
				k++;
			}
			while(w[k + 1]) k++;
			if(!w[k]) k--;
			if(w[k] && k > len) return 0;
		}
	}
	for(int i= 1; i <= len; i++)
		if(p[i] > -1 && p[i] != w[i]) return 0;
	return 1;
}

bool ch() {
	for(int i= 1; i <= n; i++) {
		if(d[i] == c[i]) continue;
		if(d[i] != ',' && c[i] != ',' && d[i] - '0' == q[i]) continue;
		if(d[i] == ',' && c[i] != ',') return 0;
		if(c[i] == ',' && d[i] != ',') return 1;
		if(d[i] - '0' < q[i]) return 0;
		return 1;
	}
	return 0;
}

void check() {
	memset(w, 0, sizeof(w));
	memset(q, 0, sizeof(q));
	len= 1;
	for(int i= 1; i <= n;) {
		if(c[i] == '0') return;
		ad();
		int r= i;
		while(c[r + 1] != ',' && r < n) r++;
		if(r - i + 1 > len) {
			if(c[i] == '?')
				q[i]= 1;
			else
				q[i]= c[i] - '0';
			for(int j= i + 1; j <= r; j++) {
				if(c[j] == '?')
					q[j]= 0;
				else
					q[j]= c[j] - '0';
			}
			int P= 0;
			for(int j= r; j >= i; j--) w[++P]= q[j];
			len= r - i + 1;
			i= r + 2;
			continue;
		}
		if(len > r - i + 1) return;
		if(i + len - 1 > n) return;
		memset(p, -1, sizeof(p));
		for(int j= i; j < i + len; j++)
			if(c[j] != '?') p[len - (j - i + 1) + 1]= c[j] - '0';
		if(!add()) return;
		for(int j= i; j <= r; j++) q[j]= w[len - j + i];
		if(len > r - i + 1) return;
		i= r + 2;
	}
	if(ch())
		for(int i= 1; i <= n; i++) {
			if(c[i] == ',')
				d[i]= ',';
			else
				d[i]= q[i] + '0';
		}
	return;
}

void dfs(int x, int l, int p) {
	if(x == n + 1) {
		if(c[n] == ',') return;
		check();
		return;
	}
	if(c[x] >= '0' && c[x] <= '9') return dfs(x + 1, l, p);
	if(c[x] == ',') {
		if(x - p - 1 >= l) return dfs(x + 1, x - p - 1, x);
		return;
	}
	if(x - p - 1 >= l) {
		c[x]= ',';
		dfs(x + 1, x - p - 1, x);
		c[x]= '?';
	}
	return dfs(x + 1, l, p);
}

int main() {
	scanf("%d", &T);
	for(; T; T--) {
		memset(b, 0, sizeof(b));
		scanf("\n%s", c + 1);
		n= strlen(c + 1);
		for(int i= 1; i <= n; i++) d[i]= 'A';
		dfs(1, 1, 0);
		if(d[1] == 'A')
			printf("impossible");
		else
			for(int i= 1; i <= n; i++) printf("%c", d[i]);
		printf("\n");
	}
}
