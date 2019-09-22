#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char num[1000006], num2[1000006], end2[1000006];
int n;
int main() {
	cin >> num, n= strlen(num);
	memcpy(num2, num, sizeof(num2));
	sort(num2, num2 + n, greater< char >());
	for(int i= n; i >= 0; i--) {
		end2[i]= end2[i] + num2[i] - num[i];
		if(end2[i] < 0) end2[i]+= 10, end2[i - 1]-= 1;
	}
    putchar(end2[n - 1] + '0'), putchar('\n');
	return 0;
}