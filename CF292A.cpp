#include <iostream>
#include <stdio.h>
using namespace std;
int n, tmpx, tmpy, ans, q, lastt;
int main(){
    cin >> n;
    for(int i= 1; i <= n; i++){
        cin >> tmpx >> tmpy;
        ans-= tmpx - lastt;
        if(ans < 0) ans= 0;
        ans+= tmpy;
        q= max(q, ans);
        lastt= tmpx;
    }
    cout << lastt + ans << ' ' << q << endl;
    return 0;
}