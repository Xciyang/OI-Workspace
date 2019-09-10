#include <iostream>
#include <stdio.h>
using namespace std;
const int mod= 1e9 + 7;
namespace Mker {
//  Powered By Kawashiro_Nitori
//  Made In Gensokyo, Nihon
#include <climits>
#define ull unsigned long long
#define uint unsigned int
ull sd;
int op;
inline void init() {
	scanf("%llu %d", &sd, &op);
}
inline ull ull_rand() {
	sd^= sd << 43;
	sd^= sd >> 29;
	sd^= sd << 34;
	return sd;
}
inline ull rand() {
	if(op == 0) return ull_rand() % USHRT_MAX + 1;
	if(op == 1) return ull_rand() % UINT_MAX + 1;
	if(op == 2) return ull_rand();
}
}  // namespace Mker
int t, ans[100000], tmp, res;
signed main() {
	scanf("%d", &t), Mker::init();
	ans[0]= (-3 + mod) % mod, ans[1]= (-6 + mod) % mod, ans[2]= (-12 + mod) % mod, tmp= 27;
	for(int i= 3; i < 100000; i++) ans[i]= ((3ll * ans[i - 1] + ans[i - 2] - 3ll * ans[i - 3] + tmp) % mod + mod) % mod, tmp= 3ll * tmp % mod;
	while(t--) res^= ans[Mker::rand()];
	printf("%d\n", res);
	return 0;
}