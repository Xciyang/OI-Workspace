#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;
int n;
struct NODE {
	long long x, y;
} a[300005], tmpn;
int tryans[300005], bestans[300005];
long long lasta, ans;
inline long long getSum(const NODE &n2) {
	return n2.x * 2 + n2.y * 2;
}
int main() {
	ifstream ifile("./1.in");
	ifile >> n;
	for(int i= 1; i <= n; i++) ifile >> a[i].x >> a[i].y;
	ifile.close();
	ifstream ifile2("./1.out");
	for(int i= 1; i <= n; i++) ifile2 >> tryans[i];
	ifile2.close();
	ifstream ifile3("./std.out");
	for(int i= 1; i <= n; i++) ifile3 >> bestans[i];
	ifile2.close();
	tmpn.x= tmpn.y= 1;
	lasta= 4, ans= 0;
	for(int i= 1; i <= n; i++) {
		tmpn.x= max(tmpn.x, a[tryans[i]].x);
		tmpn.y= max(tmpn.y, a[tryans[i]].y);
		ans= max(ans, getSum(tmpn) - lasta);
		lasta= getSum(tmpn);
	}
	long long res= ans;
	tmpn.x= tmpn.y= 1;
	lasta= 4, ans= 0;
	for(int i= 1; i <= n; i++) {
		tmpn.x= max(tmpn.x, a[bestans[i]].x);
		tmpn.y= max(tmpn.y, a[bestans[i]].y);
		ans= max(ans, getSum(tmpn) - lasta);
		lasta= getSum(tmpn);
	}
	if(res == ans) {
		cout << "ok" << endl;
		return 0;
	}
	cout << "meile" << endl;
	return 1;
}