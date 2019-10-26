#include <iostream>
#include <stdio.h>
using namespace std;
int n, a[1000006], sum;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) cin >> a[i];
	for(int i= 2, j= n - 1; i < j;) {
		while(i < n && a[i] + sum > a[i - 1]) a[i++]+= sum;
		while(j > 1 && a[j] + sum > a[j + 1]) a[j--]+= sum;
		if(i > j) break;
		sum+= min(a[i - 1] - a[i] - sum, a[j + 1] - a[j] - sum) + 1;
	}
	cout << sum << endl;
	return 0;
}