/*
///二分图的最大匹配
#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<math.h>
#include<map>
#include<queue> 
#include<unordered_map>
#include<stdlib.h>
#define double long double
using namespace std;
int n;
int m, s;
int idx;
int head[1010];
struct node {
	int v;
	int ne;
}e[50010];
int match[1010];
int vis[1010];
void add(int a, int b) {
	e[++idx] = { b,head[a] };
	head[a] = idx;
}
void input1() {
	cin >> n >> m >> s;
	int a, b;
	for (int i = 1; i <= s; i++) {
		cin >> a >> b;
		add(a, b);
	}
}
bool solve(int u) {
	for (int i = head[u]; i; i = e[i].ne) {
		int v = e[i].v;
		if (vis[v])continue;
		else {
			vis[v] = 1;
			if (!match[v] || solve(match[v])) {
				match[v] = u;
				return 1;
			}
		}
	}
	return 0;
}
int ans = 0;
int main() {
	input1();
	for (int i = 1; i <= n; i++) {
		for (int i = 1; i <= m; i++)vis[i] = 0;
		if (solve(i)) ans++;
	}
	cout << ans << endl;
	return 0;
}
*/
/*
//二分图最大权匹配
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define inf 1e18
using namespace std;
int n;
int m;
long long int w[550][550];
long long int la[550], lb[550];
long long  int slack[550];
long long int pre[550], visb[550], match[550];
void bfs(int u) {
	long long int x=0,y = 0, yy = 0;
	memset(pre, 0, sizeof(pre));
	long long int delte = inf;
	for (long long int i = 1; i <= n; i++)slack[i] = inf;
	match[y] = u;
	while (1) {
		delte = inf;
		 x = match[y]; visb[y] = 1;
		for (int i = 1; i <= n; i++) {
			if (visb[i])continue;
			if (slack[i] > la[x] + lb[i] - w[x][i]) {
				slack[i] =  la[x] + lb[i] - w[x][i];
				pre[i] = y;
			}
			if (slack[i] < delte) {
				delte = slack[i];
				yy = i;
			}
		}
		for (int i = 0; i <= n; i++) {
			if (visb[i])la[match[i]] -= delte, lb[i] += delte;
			else slack[i] -= delte;
		}
		y = yy;
		if (match[y] == -1)break;
	}
	while (y) {
		match[y] = match[pre[y]];
		y = pre[y];
	}
	return;
}
long long int KM() {
	memset(match, -1, sizeof(match));
	memset(la, 0, sizeof(la));
	memset(lb, 0, sizeof(lb));
	for (int i = 1; i <= n; i++) {
		memset(visb,0, sizeof (visb));
		bfs(i);
	}
	long long int res = 0;
	for (int i = 1; i <= n; i++) {
		if(match[i]!=-1)res += w[match[i]][i];
	}
	return res;
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			w[i][j] = -inf;
		}
	}
	long long int x, y, z;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y >> z;
		w[x][y] = z;
	}
	cout << KM()<<endl;
	for (int i = 1; i <= n; i++) {
		cout << match[i] << " ";
	}
	cout << endl;
	return 0;
}

*/
/*
//一般图的最大匹配
#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
int n, m;
int ans;
int needle;
vector<int> ma[1001];
int pre[1001];
int match[1001];
int vis[1001];
int fa[1001];
int tot[1001];
queue<int> q;
inline int find(int x) {
	while (x != fa[x]) {
		x = fa[x] = fa[fa[x]];
	}
	return x;
}
inline int lca(int x,int y) {
	needle++;
	while (1) {
		if (x) {//x和y的深度可能会不同
			x = find(x);
			if (tot[x] == needle) return x;
			tot[x] = needle;
			x = pre[match[x]];
		}
		swap(x, y);
	}
}
inline void flower(int x, int y, int l) {
	while (find(x)!=l) {
		pre[x] = y; y = match[x]; vis[y] = 1; q.push(y);
		if (find(x) == x)fa[x] = l;
		if (find(y) == y)fa[y] = l;
		x = pre[y];
	}
}
inline void bfs(int cur) {
	for (int i = 1; i <= n; i++)pre[i] = vis[i] = 0, fa[i] = i;
	while (!q.empty())q.pop();
	q.push(cur); vis[cur] = 1;
	while (!q.empty()) {
		int x = q.front();q.pop();
		for (int y : ma[x]) {
			if (find(y) != find(x) && vis[y] != 2) {
				if (vis[y] ==1) {
					int l = lca(x, y);
					flower(x, y, l); flower(y, x, l);
					continue;
				}
				pre[y] = x, vis[y] = 2;
				if (!match[y]) {
					int px = y;
					while (px) {
						int py = pre[px];
						int pz = match[py];
						match[px] = py;
						match[py] = px;
						px = pz;
					}
					ans++;
					return;
				}
				vis[match[y]] = 1;
				q.push(match[y]);
			}
		}
	}
}
int main() {
	cin >> n >> m;

	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		ma[a].push_back(b), ma[b].push_back(a);
	}
	for (int i = 1; i <= n; i++)if (!match[i])bfs(i);
	cout << ans << endl;
	for (int i = 1; i <= n; i++) {
		cout << match[i] << " ";
	}
	return 0;
}
*/