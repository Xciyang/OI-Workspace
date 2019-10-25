#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
#define N 2000050
#define M 1000050
#define INF 0x7f7f7f7f
int n, m, vis[N], cnt[N], dis[N], num, head[N];
struct node {
	int next, to, dis;
} edge[M * 2];
void addedge(int u, int v, int w) {
	edge[++num]= (node){head[u], v, w};
	head[u]= num;
}
bool spfa(int s) {
	int cntt= 0;
	deque< int > q;
	for(int i= 0; i <= n + 1; i++) vis[i]= 0, dis[i]= INF;
	dis[s]= 0;
	vis[s]= 1;
	cnt[s]= 1;
	q.push_back(s);
	while(!q.empty()) {
		int u= q.front();
		q.pop_front();
		vis[u]= 0;
		for(int i= head[u]; i; i= edge[i].next) {
			int v= edge[i].to;
			if(dis[v] > dis[u] + edge[i].dis) {
				cntt++;
				if(cntt > 9999999) return 0;
				dis[v]= dis[u] + edge[i].dis;
				if(!vis[v]) {
					vis[v]= 1;
					if(dis[v] > dis[q.front()] || q.empty())
						q.push_back(v);
					else
						q.push_front(v);
					cnt[v]++;
					if(cnt[v] >= n) return 0;
				}
			}
		}
	}
	return 1;
}
int main() {
	scanf("%d%d", &n, &m);
	int a, b;
	for(int i= 1; i <= m; i++) scanf("%d%d", &a, &b), addedge(a - 1, b, 1), addedge(b, a - 1, -1);
	for(int i= 0; i <= n - 1; i++) addedge(i, i + 1, 1), addedge(i + 1, i, 0);
	if(!spfa(0)) {
		printf("-1");
		return 0;
	}
	int answer= 0;
	printf("%d", dis[n]);
	return 0;
}
