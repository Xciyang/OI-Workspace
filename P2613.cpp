#include <iostream>
#include <stdio.h>
using namespace std;
int a, b, p= 19260817;
int read() {
	int e= 0;
	char ch= getchar();
	while(ch < '0' || ch > '9') ch= getchar();
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar(), e%= p;
    return e;
}
int exgcd(int _a, int _b, int &x, int &y){
    if(!_b){
        x= 1, y= 0;
        return _a;
    }
    int res= exgcd(_b, _a % _b, x, y), lx= x;
    x= y, y= lx - _a / _b * y;
    return res;
}
int main() {
    a= read();
    b= read();
    if(!b){
        cout << "Angry!" << endl;
        return 0;
    }
    int x, y;
    exgcd(b, p, x, y);
    x = (x % p + p) % p;
    cout << (long long)a * x % p << endl;
	return 0;
}