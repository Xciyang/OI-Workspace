#include <bits/stdc++.h>

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

inline int power(int x, int y, int mod, int res = 1) {
    for (; y; y >>= 1, x = 1ll * x * x % mod) {
        if (y & 1) { res = 1ll * res * x % mod; }
    } return res;
}

const int N = 5e5 + 5, L = 19;

int n, m, q, lgn, e[L][N], bln[N], pos[N];
std::vector<int> cyc[N];

int check(int x, int y) {
    if (x == 1) { return 1; }
    long long tmp = 1;
    for (; y; y--) {
        tmp *= x;
        if (tmp > n) { return -1; }
    } return tmp;
}

int jump(int u, int x) {
    for (int i = 0; i <= lgn; i++) {
        if (1 << i & x) { u = e[i][u]; }
    } return u;
}

int main() {
    n = read(); lgn = log(n) / log(2) + 1e-7;
    for (int i = 1; i <= n; i++) {
        e[0][i] = read(); bln[i] = -1;
    }
    for (int j = 1; j <= lgn; j++) {
        for (int i = 1; i <= n; i++) {
            e[j][i] = e[j - 1][e[j - 1][i]];
        }
    }
    for (int i = 1; i <= n; i++) {
        int u = e[lgn][e[lgn][i]];
        if (bln[u] == -1) {
            for (; bln[u] == -1; u = e[0][u]) {
                bln[u] = m; pos[u] = cyc[m].size();
                cyc[m].push_back(u);
            }
            m++;
        }
    }
    for (q = read(); q; q--) {  
        int u = read(), x = read(), y = read(), z = check(x, y);
        if (z == -1) {
            u = jump(u, n);
            int s = cyc[bln[u]].size();
            z = (power(x, y, s) + s - n % s) % s;
            u = cyc[bln[u]][(pos[u] + z) % s];
        } else {
            u = jump(u, z);
        } printf("%d\n", u);
    }
    return 0;
}