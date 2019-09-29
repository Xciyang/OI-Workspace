#include <iostream>
#include <stdio.h>
using namespace std;
int s, t, tmpx;
int main() {
    scanf("%d:%d", &s, &tmpx);
	s= s * 60 + tmpx;
    scanf("%d:%d", &t, &tmpx);
	t= t * 60 + tmpx;
	if(s < t) s+= 24 * 60;
	s-= t;
    printf("%02d:%02d\n", s / 60, s % 60);
	return 0;
}