#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;
struct CTRIE {
	struct NODE {
		int pasts, endmark;
		NODE *son[26];
	} MNODE;
	void insert(const char *str, int len) {
		NODE *p= &MNODE;
		for(int i= 0, ch; i < len; i++) {
			ch= str[i] - 'a';
			if(!p->son[ch]) p->son[ch]= new NODE();
			p= p->son[ch], ++p->pasts;
		}
		p->endmark= 1;
		return;
	}
};
int main() {
	return 0;
}