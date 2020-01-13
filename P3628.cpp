#include <iostream>
#include <stdio.h>
using namespace std;
long long n, a, b, c, f[1000006], x[1000006], sum[1000006];
int qu[1000006], head = 0, tail = 0;
inline long long X(int i) {
	return sum[i];
}
inline long long Y(int i) {
	return f[i] + a * sum[i] * sum[i] - b * sum[i];
}
inline double K(int i, int j) {
	return (double)(Y(j) - Y(i)) / (X(j) - X(i));
}
int main() {
	cin >> n >> a >> b >> c;
	for(int i = 1; i <= n; i++) cin >> x[i], sum[i] = sum[i - 1] + x[i];
	f[0] = 0;
	for(int i = 1; i <= n; i++) {
		while(head < tail && K(qu[head], qu[head + 1]) >= 2 * a * sum[i]) ++head;
		f[i] = f[qu[head]] + a * (sum[i] - sum[qu[head]]) * (sum[i] - sum[qu[head]]) + b * (sum[i] - sum[qu[head]]) + c;
		while(head < tail && K(qu[tail - 1], qu[tail]) <= K(qu[tail], i)) --tail;
		qu[++tail] = i;
	}
	cout << f[n] << endl;
	return 0;
}