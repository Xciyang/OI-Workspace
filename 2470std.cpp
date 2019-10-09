#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 55, INF = 0x3f3f3f3f;
int n, f[N][N][2]; char s[N];
int dfs(int l, int r, int op) {
    if (f[l][r][op] != -1) return f[l][r][op];
    if (l == r) return f[l][r][op] = 2;
    int i, res = INF; if (op) {
        res = r - l + 2; int mid; bool flag = 1;
        if (!(r - l & 1)) flag = 0;
        mid = l + r >> 1; for (i = l; i <= mid; i++)
            if (s[i] != s[mid + i - l + 1]) flag = 0;
        if (flag) res = min(res, dfs(l, mid, 1) + 1);
        for (i = l; i < r; i++) res = min(res, dfs(l, i, 1) + r - i);
    }
    else for (i = l; i < r; i++) {
        res = min(res, dfs(l, i, 0) + dfs(i + 1, r, 0));
        if (i + 1 < r) res = min(res, dfs(l, i, 0) + dfs(i + 1, r, 1));
        if (l < i) res = min(res, dfs(l, i, 1) + dfs(i + 1, r, 0));
        if (l < i && i + 1 < r) res = min(res, dfs(l, i, 1) + dfs(i + 1, r, 1));
    }
    return f[l][r][op] = res;
}
int main() {
    memset(f, -1, sizeof(f));
    scanf("%s", s + 1); n = strlen(s + 1);
    dfs(1, n, 0); dfs(1, n, 1);
    cout << min(f[1][n][0], f[1][n][1]) - 1 << endl;
    return 0;
}