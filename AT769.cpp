#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, ans;
char tmp[2][10];
int main() {
	cin >> n;
	while(n--) {
		cin >> tmp[m];
		for(int i= 0; i < 9; i++) ans+= (tmp[m][i] == 'x' || (tmp[m][i] == 'o' && tmp[m ^ 1][i] != 'o'));
		m^= 1;
	}
    cout << ans << endl;
	return 0;
}