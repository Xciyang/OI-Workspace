#include <iostream>
#include <stdio.h>
#include <queue>
#define int long long
using namespace std;
int n, c[50005], l, a[50005], b[50005], f[50005];
deque< int > qu;
inline double xl(int i, int j) {
    return (((double)f[i] + b[i] * b[i]) - (f[j] + b[j] * b[j])) / (b[i]- b[j]);
}
signed main() { 
    cin >> n >> l;
    for(int i= 1; i <= n; i++) cin >> c[i], c[i]+= c[i - 1], a[i]= c[i] + i, b[i]= a[i] + l + 1;
    b[0]= l+ 1, qu.push_back(0);
    for(int i= 1, j; i <= n;i ++){
        while(qu.size() > 1){
            j= qu.front(), qu.pop_front();
            if(xl(j, qu.front()) > 2 * a[i]) {
                qu.push_front(j);
                break;
            }
        }
        j= qu.front(), f[i]= f[j] + (a[i] - b[j]) * (a[i] - b[j]);
        cerr << j << endl;
        while(qu.size() > 1) {
            j= qu.back(), qu.pop_back();
            if(xl(i, qu.back()) > xl(qu.back(), j)) {
                qu.push_back(j);
                break;
            }
        }
        qu.push_back(i);
    }
    cout << f[n] << endl;
    return 0;
}