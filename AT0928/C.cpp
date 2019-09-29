#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
struct NODE {
	int id, l;
	inline int operator<(const NODE &n2) const {
		return l < n2.l;
	}
} no[100005];
int n;
int main() {
	cin >> n;
	for(int i= 1; i <= n; i++) no[i].id= i, cin >> no[i].l;
	sort(no + 1, no + n + 1);
	for(int i= 1; i <= n; i++) cout << no[i].id << ' ';
	cout << endl;
	return 0;
}