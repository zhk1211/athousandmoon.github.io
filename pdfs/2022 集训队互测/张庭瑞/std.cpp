#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, X[N][3], W[N], ps[N], dfn[N * 6], low[N * 6], dfc, tp, stk[N * 6], instk[N * 6], bel[N * 6], scc;
vector<int> S[N], G[N * 6];
void add_edge(int u, int x, int v, int y) {
	G[u * 2 + x].push_back(v * 2 + y);
}
void Tarjan(int u) {
	dfn[u] = low[u] = ++dfc;
	stk[++tp] = u;
	instk[u] = 1;
	for (int v : G[u]) {
		if (!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (instk[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		int w;
		++scc;
		do {
			w = stk[tp--];
			instk[w] = 0;
			bel[w] = scc;
		} while (w != u);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d%d", &X[i][0], &X[i][1], &X[i][2], &W[i]);
		S[X[i][0]].push_back(W[i]);
		S[X[i][1]].push_back(W[i]);
		S[X[i][2]].push_back(W[i]);
	}
	for (int i = 1; i <= n; i++) {
		sort(S[i].begin(), S[i].end());
		S[i].resize(unique(S[i].begin(), S[i].end()) - S[i].begin());
		ps[i] = ps[i - 1] + S[i].size();
		if (!S[i].empty()) {
			add_edge(ps[i - 1], 0, ps[i - 1], 1);
			for (int j = 1; j < (int)S[i].size(); j++) {
				int x = ps[i - 1] + j - 1, y = ps[i - 1] + j;
				add_edge(x, 0, y, 0);
				add_edge(y, 1, x, 1);
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		int id[3];
		for (int j = 0; j < 3; j++) {
			id[j] = lower_bound(S[X[i][j]].begin(), S[X[i][j]].end(), W[i]) - S[X[i][j]].begin();
		}
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < j; k++) {
				int x = ps[X[i][j] - 1] + id[j], y = ps[X[i][k] - 1] + id[k];
				add_edge(x, 0, y, 1);
				add_edge(y, 0, x, 1);
				if (id[j] < (int)S[X[i][j]].size() - 1 && id[k] < (int)S[X[i][k]].size() - 1) {
					x++, y++;
					add_edge(x, 1, y, 0);
					add_edge(y, 1, x, 0);
				}
			}
		}
	}
	for (int i = 0; i < ps[n] * 2; i++) if (!dfn[i]) {
		Tarjan(i);
	}
	for (int i = 0; i < ps[n]; i++) if (bel[i * 2] == bel[i * 2 + 1]) {
		puts("NO");
		return 0;
	}
	puts("YES");
	for (int i = 1; i <= n; i++) {
		if (S[i].empty()) {
			printf("1");
		} else {
			int cur = S[i].back();
			for (int j = 1; j < (int)S[i].size(); j++) {
				if (bel[(ps[i - 1] + j) * 2] < bel[(ps[i - 1] + j) * 2 + 1]) {
					cur = S[i][j - 1];
					break;
				}
			}
			printf("%d", cur);
		}
		printf("%c", " \n"[i == n]);
	}
	return 0;
}
