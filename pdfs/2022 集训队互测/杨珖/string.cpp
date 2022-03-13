#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int mod = 998244353, N = 115;

int n, k, m, z[N];

int add(int x, int y) { return x + y < mod ? x + y : x + y - mod; }
int sub(int x, int y) { return x < y ? x + mod - y : x - y; }
int power(int a, int n) {
  int tp = 1;
  while (n) {
    if (n & 1) tp = 1ll * tp * a % mod;
    a = 1ll * a * a % mod, n >>= 1;
  }
  return tp;
}

namespace task0 {
int f[1 << 21], g[1 << 21];

int _count(int x) { return 2 * __builtin_popcount(x) - k + 1; }
int solve() {
  for (int s = 0; s < (1 << (k - 1)); s++)
    if (_count(s) > 0) f[s] = 1;
  for (int i = n - 1; i >= k - 1; i--) {
    for (int s = 0; s < (1 << (k - 1)); s++) {
      int x = _count(s);
      if (x < 1) continue;
      g[s] = f[s >> 1 | 1 << (k - 2)];
      if (x > 1) g[s] = add(g[s], f[s >> 1]);
    }
    memcpy(f, g, (1 << (k - 1)) << 2);
  }

  int ans = 0, t0 = 0, t1 = 0;
  for (int i = 0; i < m; i++) t0 |= z[i] << i, t1 |= (z[i] ^ 1) << i;
  for (int s = 0; s < (1 << (k - 1 - m)); s++) ans = add(ans, add(f[s << m | t0], f[s << m | t1]));
  return ans;
}
}  // namespace task0

namespace task1 {
int a[6], b[6][6], f[N][N], ans, t, tot;
int s[N], c[N][N], g[N][N], h[N][N];
int f0[N][N], f1[N][N][N], limit[N];

int det(int n) {
  static int f[1 << 6];
  n++, f[0] = 1;
  for (int s = 1; s < (1 << n); s++) {
    int p = __builtin_popcount(s) - 1, op = (p & 1) ? 1 : -1;
    f[s] = 0;
    for (int x = 0; x < n; x++)
      if (s >> x & 1) op = -op, f[s] = (f[s] + 1ll * op * f[s ^ 1 << x] * b[p][x]) % mod;
  }
  int x = f[(1 << n) - 1];
  return x < 0 ? x + mod : x;
}

void work(int q) {
  static int s[6];
  for (int i = 1; i <= q; i++) s[i] = s[i - 1] + a[i];

  for (int j = 0; j < q; j++) {
    int y = s[j + 1] + k / 2;
    b[0][j] = f0[s[q] + t][y];
  }
  if (m <= n % k) b[0][q] = c[n % k - m][s[q] + t - tot];
  for (int i = 1; i <= q; i++) {
    for (int j = 0; j < q; j++) {
      int x = s[i], y = s[j + 1] + k / 2;
      b[i][j] = f1[x][y][s[q] + t];
    }
    b[i][q] = g[s[i]][s[q] + t];
  }

  ans = add(ans, det(q));
}

void get(int lim) {
  static int f[N][N];
  memset(f, 0, sizeof f);
  f[m][s[k]] = 1;
  for (int i = m + 1; i <= k; i++)
    for (int j = tot; j <= (i <= n % k ? lim : n); j++)
      f[i][j] = add(f[i - 1][j], f[i - 1][j - 1]);
  for (int i = 0; i <= n; i++) f0[lim][i] = f[k][i];
}

void dfs(int i) {
  if (i * k > n) {
    work(i - 1);
    return;
  }

  if (i > 1)
    for (int j = 1; j <= k / 2; j++) a[i] = j, dfs(i + 1);
  else
    for (int j = max(k / 2 + 1, tot) - k / 2; j <= k - m + s[m] - k / 2; j++) a[i] = j, dfs(i + 1);
}

int solve() {
  ans = 0;
  memset(f, 0, sizeof f), memset(g, 0, sizeof g), memset(h, 0, sizeof h);

  c[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; j++)
      c[i][j] = add(c[i - 1][j], c[i - 1][j - 1]);
  }

  for (int i = 1; i <= k; i++) s[i] = s[i - 1] + z[i];
  for (int i = 0; i < m; i++) limit[i] = s[i] + 1;
  for (int i = m; i <= k; i++) limit[i] = s[k];
  tot = s[k];

  for (int i = limit[n % k]; i <= n; i++) g[i][i] = 1;
  for (int t = n % k - 1; t != -1; t--)
    for (int i = limit[t]; i <= n; i++)
      for (int j = i; j <= n; j++)
        g[i][j] = add(g[i][j], g[i + 1][j]);

  for (int i = limit[k]; i <= n; i++) h[i][i] = 1;
  for (int t = k - 1; t >= n % k; t--)
    for (int i = limit[t]; i <= n; i++)
      for (int j = i; j <= n; j++)
        h[i][j] = add(h[i][j], h[i + 1][j]);

  for (int i = 0; i <= n; i++)
    for (int j = i; j <= n; j++) {
      for (int t = i; t <= j; t++)
        f1[i][j][t] = (f1[i][j][t - 1] + 1ll * g[i][t] * h[t][j]) % mod;
      for (int t = j + 1; t <= n; t++) f1[i][j][t] = f1[i][j][t - 1];
    }

  for (int i = 0; i <= n; i++) get(i);

  for (t = 0; t <= n % k; t++) dfs(1);

  return ans;
}
}  // namespace task1

int main() {
  cin >> n >> k >> m;
  for (int i = 0; i < m; i++) scanf("%1d", z + i);

  if (k <= 22)
    cout << task0::solve();
  else {
    for (int i = m; i; i--) z[i] = z[i - 1];
    z[0] = 0;
    int ans = task1::solve();
    for (int i = 1; i <= m; i++) z[i] ^= 1;
    cout << add(ans, task1::solve());
  }
}