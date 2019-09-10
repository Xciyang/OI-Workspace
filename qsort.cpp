#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;
inline int read() {
	int re= 0;
	char c= getchar();
	while(c > '9' || c < '0') c= getchar();
	while(c >= '0' && c <= '9') re= re * 10 + c - '0', c= getchar();
	return re;
}
template < class T >
inline void write(T x) {
	if(x > 9) write(x / 10);
	putchar('0' + x % 10);
	return;
}
int n, a[1000001], b[1000001];
void msortmain(int begin, int mid, int end) {
	int front= begin, middle= mid + 1, times= 0;
	while(front != mid + 1 && middle != end + 1) {
		if(a[front] > a[middle]) {
			b[times++]= a[middle++];
		}
		else {
			b[times++]= a[front++];
		}
	}
	while(front != mid + 1) b[times++]= a[front++];
	while(middle != end + 1) b[times]= b[middle++];
	for(int i= 0; i < times; i++) a[begin + i]= b[i];
	return;
}
void msort(int begin, int end) {
	if(begin < end) {
		int mid= (begin + end) / 2;
		msort(begin, mid);
		msort(mid + 1, end);
		msortmain(begin, mid, end);
	}
	return;
}
int main() {
	int n;
	n= read();
	for(int i= 0; i < n; i++) a[i]= read();
	msort(0, n - 1);
	for(int i= 0; i < n; i++) write(a[i]), putchar(' ');
	return 0;
}