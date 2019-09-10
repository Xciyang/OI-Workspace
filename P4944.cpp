#include <iostream>
#include <stdio.h>
#include <deque>
#include <algorithm>
using namespace std;
typedef pair< int, int > Pos, Ans;
int n, m, k, idd, mappping[256], ans, flag[300][300];
char nowmap[300][300], opp[30][200];
deque< Pos > s[30];
int moves[4][2]= {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
Ans anss[30];
int cmpans(const Ans &a1, const Ans &a2) {
	return a1.first > a2.first || (a1.first == a2.first && a1.second < a2.second);
}
inline int crosslimit(int nowx, int nowy) {
	return nowx < 1 || nowx > n || nowy < 1 || nowy > m;
}
void dfs(int nowx, int nowy, int id) {
	if(nowmap[nowx][nowy] != '#' && (nowmap[nowx][nowy] != '@' || s[id].size())) return;
	if(flag[nowx][nowy]) return;
	nowmap[nowx][nowy]= '#', flag[nowx][nowy]= 1;
	s[id].push_back(Pos(nowx, nowy));
	for(int i= 0; i < 4; i++) dfs(nowx + moves[i][0], nowy + moves[i][1], id);
	return;
}
void moved(int id, char ch) {
	int fx= s[id].front().first, fy= s[id].front().second;
	int ex= fx + moves[mappping[ch]][0], ey= fy + moves[mappping[ch]][1];
	if(crosslimit(ex, ey) || nowmap[ex][ey] == '#') {
		while(!s[id].empty()) nowmap[s[id].front().first][s[id].front().second]= '&', s[id].pop_front();
		return;
	}
	if(nowmap[ex][ey] != '&') {
		fx= s[id].back().first, fy= s[id].back().second, s[id].pop_back();
		nowmap[fx][fy]= '.';
	}
	s[id].push_front(Pos(ex, ey)), nowmap[ex][ey]= '#';
	return;
}
void printmap() {
	for(int i= 1; i <= n; i++) {
		for(int j= 1; j <= m; j++) cout << nowmap[i][j];
		cout << endl;
	}
	cout << endl;
	return;
}
int main() {
	cin >> n >> m >> k;
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= m; j++) cin >> nowmap[i][j];
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= m; j++)
			if(nowmap[i][j] == '@') dfs(i, j, ++idd);
	for(int i= 1; i <= idd; i++)
		for(int j= 1; j <= k; j++) cin >> opp[i][j];
	mappping['W']= 0, mappping['A']= 1, mappping['D']= 2, mappping['S']= 3;
	for(int i= 1; i <= k; i++)
		for(int j= 1; j <= idd; j++) {
			if(s[j].empty()) continue;
			moved(j, opp[j][i]);
		}
	for(int i= 1; i <= idd; i++) anss[i].first= s[i].size(), anss[i].second= i;
	sort(anss + 1, anss + idd + 1, cmpans);
	for(int i= 1; i <= idd; i++) cout << anss[i].first << ' ' << anss[i].second << endl;
	for(int i= 1; i <= n; i++)
		for(int j= 1; j <= m; j++)
			if(nowmap[i][j] == '&') ++ans;
	cout << ans << endl;
	return 0;
}