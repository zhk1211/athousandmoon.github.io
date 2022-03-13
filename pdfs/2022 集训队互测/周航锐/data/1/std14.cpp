#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
inline void Add(int &x, int y) { if ((x += y) >= mod) x -= mod; }
inline constexpr int power(int a, int b) {
    long long res = a, ans = 1;
    for (; b; b >>= 1, res = res * res % mod) if (b & 1) ans = ans * res % mod;
    return ans;
}
const int T = 8, N = power(6, T), M = 1 << T;
vector < int > sze[T + 1], rev[T + 1];
int tmp[N];
int a[N], b[N], c[N];
int A[M][M], B[M][M], C[M][M];
const int f[6][6] = {
    {1, 0, 0, 1, 1, 1},
    {1, mod - 1, 0, mod - 1, 1, mod - 1},
    {0, 1, 1, 0, 1, mod - 1},
    {mod - 1, 1, mod - 1, 0, 1, 1},
    {0, mod - 1, 1, mod - 1, 1, 1},
    {mod - 1, 0, mod - 1, 1, 1, mod - 1},
};
const int g[6][6] = {
    {332748118, 332748118, 0, 0, 665496235, 665496235},
    {0, 0, 332748118, 332748118, 665496235, 665496235},
    {0, 665496235, 332748118, 665496235, 332748118, 0},
    {332748118, 665496235, 0, 665496235, 0, 332748118},
    {166374059, 166374059, 166374059, 166374059, 166374059, 166374059},
    {166374059, 831870294, 831870294, 166374059, 166374059, 831870294},
};
void trans(int a[], int n, int tp) {
    if (n == 1) return;
    int m = n / 6;
    for (int i = 0; i < 6; i++) trans(a + m * i, m, tp);
    memset(tmp, 0, sizeof(int) * n);
    for (int i = 0; i < 6; i++) {
        int st1 = i * m;
        for (int j = 0; j < 6; j++) {
            int st2 = j * m;
            int t = (tp == 1 ? f : g)[i][j];
            if (t == 0) continue;
            for (int k = 0; k < m; k++) tmp[st2 + k] = (tmp[st2 + k] + 1ll * a[st1 + k] * t) % mod;
        }
    }
    memcpy(a, tmp, sizeof(int) * n);
}
inline int mInv(int ans[][M], int a[][M], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) ans[i][j] = i == j;
    for (int i = 0; i < n; i++) {
        if (a[i][i] == 0) {
            for (int j = i + 1; j < n; j++) if (a[i][j]) {
                swap(a[i], a[j]);
                swap(b[i], b[j]);
            }
        }
        if (a[i][i] == 0) return 0;
        int inv = power(a[i][i], mod - 2);
        for (int j = i; j < n; j++) a[i][j] = 1ll * a[i][j] * inv % mod;
        for (int j = 0; j < n; j++) ans[i][j] = 1ll * ans[i][j] * inv % mod;
        for (int j = 0; j < n; j++) if (i != j) {
            int t = mod - a[j][i];
            for (int k = i; k < n; k++) a[j][k] = (a[j][k] + 1ll * a[i][k] * t) % mod;
            for (int k = 0; k < n; k++) ans[j][k] = (ans[j][k] + 1ll * ans[i][k] * t) % mod;
        }
    }
    return 1;
}
inline int inv(int ans[], int a[], int l) {
    int cnt = 0;
    for (auto i : sze[l]) {
        int ccnt = cnt;
        for (int x = 0; x < i; x++)
            for (int y = 0; y < i; y++) {
                A[x][y] = a[rev[l][cnt]];
                cnt++;
            }
        if (mInv(B, A, i) == 0) return 0;
        for (int x = 0; x < i; x++)
            for (int y = 0; y < i; y++) {
                ans[rev[l][ccnt++]] = B[x][y];
            }
    }
    return 1;
}
int main() {
    int n = 1, l;
    scanf("%d", &l);
    for (int i = 0; i < l; i++) n *= 6;
    sze[0].push_back(1);
    rev[0].push_back(0);
    for (int i = 1, cur = 1; i <= l; i++, cur *= 6) {
        for (auto j : sze[i - 1]) sze[i].push_back(j * 2);
        for (auto j : sze[i - 1]) sze[i].push_back(j);
        for (auto j : sze[i - 1]) sze[i].push_back(j);
        int p[6] = {0};
        for (auto j : sze[i - 1]) {
            for (int x = 0; x < j; x++) {
                for (int y = 0; y < j; y++) rev[i].push_back(rev[i - 1][p[0]++] + 0 * cur);
                for (int y = 0; y < j; y++) rev[i].push_back(rev[i - 1][p[1]++] + 1 * cur);
            }
            for (int x = 0; x < j; x++) {
                for (int y = 0; y < j; y++) rev[i].push_back(rev[i - 1][p[2]++] + 2 * cur);
                for (int y = 0; y < j; y++) rev[i].push_back(rev[i - 1][p[3]++] + 3 * cur);
            }
        }
        for (auto j : rev[i - 1]) rev[i].push_back(j + 4 * cur);
        for (auto j : rev[i - 1]) rev[i].push_back(j + 5 * cur);
    }
    int m = 1;
    for (int i = 0; i < n; i++) scanf("%d", &a[i]), Add(m, a[i]);
    m = power(m, mod - 2);
    for (int i = 0; i < n; i++) a[i] = 1ll * a[i] * (mod - m) % mod;
    Add(a[0], 1);
    trans(a, n, 1);
    if (inv(b, a, l) == 0) return puts("-1"), 0;
    trans(b, n, -1);
    for (int i = 0; i < n; i++) b[i] = 1ll * b[i] * m % mod;
    int ans = 0;
    for (int i = 0; i < n; i++) ans ^= b[i];
    printf("%d\n", ans);
}