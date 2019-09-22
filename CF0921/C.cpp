#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
struct BLOCK {
	int x1, y1, x2, y2;
	long long s;
} wh, bl[2];
long long calc() {
	if(bl[0].x1 > bl[1].x2 || bl[0].x2 < bl[1].x1 || bl[0].y1 > bl[1].y2 || bl[0].y2 < bl[1].y1) return 0;
	long long len= min(bl[0].x2, bl[1].x2) - max(bl[0].x1, bl[1].x1);
	long long wid= min(bl[0].y2, bl[1].y2) - max(bl[0].y1, bl[1].y1);
	return len * wid;
}
int main() {
	cin >> wh.x1 >> wh.y1 >> wh.x2 >> wh.y2;
	wh.s= 1LL * (wh.x2 - wh.x1) * (wh.y2 - wh.y1);
	for(int i= 0; i < 2; i++) cin >> bl[i].x1 >> bl[i].y1 >> bl[i].x2 >> bl[i].y2;
	for(int i= 0; i < 2; i++) {
		bl[i].x1= max(bl[i].x1, wh.x1);
		bl[i].x2= min(bl[i].x2, wh.x2);
		bl[i].y1= max(bl[i].y1, wh.y1);
		bl[i].y2= min(bl[i].y2, wh.y2);
		if(bl[i].x2 - bl[i].x1 <= 0 || bl[i].y2 - bl[i].y1 <= 0)
			bl[i].s= 0;
		else
			bl[i].s= 1LL * (bl[i].x2 - bl[i].x1) * (bl[i].y2 - bl[i].y1);
	}
	if(bl[0].s) wh.s-= bl[0].s;
	if(bl[1].s) wh.s-= bl[1].s;
	if(bl[0].s > 0 && bl[1].s > 0) wh.s+= calc();
	cout << string(wh.s <= 0 ? "NO" : "YES") << endl;
	return 0;
}