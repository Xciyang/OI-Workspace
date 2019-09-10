#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
struct IOBUF {
	struct {
		char buff[1 << 24], *p, *pend;
	} in;
	struct {
		char buff[1 << 24], *p;
	} out;
	IOBUF() {
		in.p= in.buff, out.p= out.buff, in.pend= in.buff + fread(in.buff, 1, 1 << 24, stdin);
	}
	~IOBUF() {
		fwrite(out.buff, 1, out.p - out.buff, stdout);
	}
} IOB;
#define getchar() (*(IOB.in.p++))
#define putchar(c) (*(IOB.out.p++)= (c))
int read() {
	int e= 0;
	char ch= getchar();
	while(ch < '0' || ch > '9') ch= getchar();
	while(ch >= '0' && ch <= '9') e= e * 10 + ch - '0', ch= getchar();
	return e;
}
const int sqrtn= 1300;
struct BLOCK {
	int siz, nxt;
	char ch[sqrtn << 1];
} b[sqrtn << 2];
int blocks[sqrtn << 2], bp, cur;
inline void init() {
	for(int i= 1; i < (sqrtn << 2); i++) blocks[i]= i;
	b[0].nxt= -1, bp= 1;
	return;
}
inline int newb() {
	return blocks[bp++];
}
inline void delb(int x) {
	blocks[--bp]= x;
	return;
}
inline void add(int x, int y, char *st, int siz) {
	if(y != -1) b[y].nxt= b[x].nxt, b[y].siz= siz, memcpy(b[y].ch, st, siz);
	b[x].nxt= y;
	return;
}
inline int pos(int &x) {
	// &x
	int res= 0;
	while(res != -1 && b[res].siz < x) x-= b[res].siz, res= b[res].nxt;
	return res;
}
void split(int x, int p) {
	if(x == -1 || p == b[x].siz) return;
	add(x, newb(), b[x].ch + p, b[x].siz - p);
	b[x].siz= p;
	return;
}
void merge(int x, int y) {
	memcpy(b[x].ch + b[x].siz, b[y].ch, b[y].siz);
	b[x].siz+= b[y].siz, b[x].nxt= b[y].nxt, delb(y);
	return;
}
void insert(int w, int siz, char *st) {
	int nowp= pos(w);
	split(nowp, w);
	int nextp, fp= nowp;
	while(sqrtn < siz) {
		nextp= newb();
		add(nowp, nextp, st, sqrtn);
		st+= sqrtn, siz-= sqrtn, nowp= nextp;
	}
	nextp= newb(), add(nowp, nextp, st, siz);
	if(b[nextp].nxt != -1 && b[nextp].siz + b[b[nextp].nxt].siz < sqrtn) merge(nextp, b[nextp].nxt);
	if(b[fp].nxt != -1 && b[fp].siz + b[b[fp].nxt].siz < sqrtn) merge(fp, b[fp].nxt);
	return;
}
void erase(int w, int siz) {
	int nowp= pos(w);
	split(nowp, w);
	int nextp= b[nowp].nxt;
	while(siz > b[nextp].siz) siz-= b[nextp].siz, b[nowp].nxt= b[nextp].nxt, delb(nextp), nextp= b[nowp].nxt;
	split(nextp, siz), b[nowp].nxt= b[nextp].nxt, delb(nextp);
	while(b[nowp].nxt != -1 && b[nowp].siz + b[b[nowp].nxt].siz < sqrtn) merge(nowp, b[nowp].nxt);
	return;
}
void get(int w, int siz) {
	int nowp= pos(w), mins;
	mins= min(siz, b[nowp].siz - w), siz-= mins;
	for(int i= w; i < w + mins; i++) putchar(b[nowp].ch[i]);
	while(siz) {
		nowp= b[nowp].nxt, mins= min(siz, b[nowp].siz), siz-= mins;
		for(int i= 0; i < mins; i++) putchar(b[nowp].ch[i]);
	}
	putchar('\n');
	return;
}
char readopt() {
	char ch= getchar();
	while(ch != 'M' && ch != 'I' && ch != 'D' && ch != 'G' && ch != 'P' && ch != 'N') ch= getchar();
	return ch;
}
int m, n;
char str[1048576];
int main() {
	init(), m= read();
	while(m--) {
		switch(readopt()) {
			case 'M': cur= read(); break;
			case 'P': --cur; break;
			case 'N': ++cur; break;
			case 'I': {
				n= read();
				for(int i= 0; i < n; i++) {
					str[i]= getchar();
					if(str[i] < 32 || str[i] > 126) --i;
				}
				insert(cur, n, str);
				break;
			}
			case 'D': {
				n= read();
				erase(cur, n);
				break;
			}
			case 'G': {
				n= read();
				get(cur, n);
				break;
			}
			default: break;
		}
	}
	return 0;
}