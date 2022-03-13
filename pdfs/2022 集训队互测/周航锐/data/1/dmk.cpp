#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int fn[] = {0, 1,1,1,  2,2,3,3, 7,8,8,8, 4,4,4, 5,6,7,8,8,8};
char tp[] = " NNNNNNNAAAANNNNNNNNN";
int f[1700010];
inline void rmain(int l, int tp) {
    int n = 1;
    for (int i = 0; i < l; i++) n *= 6;
    printf("%d\n", l);
    if (tp == 'N') {
        for (int i = 0; i < n; i++) printf("%d%c", rand() % 998244353, " \n"[i == n - 1]);
    }
    else if (tp == 'A') {
        for (int i = 0; i < n; i++) {
            int tag = 1, chk = i;
            while (chk) {
                int cur = chk % 6;
                chk /= 6;
                if (cur != 0 && cur != 3 && cur != 4) tag = 0;
            }
            printf("%d%c", tag ? rand() % 998244353 : 0, " \n"[i == n - 1]);
        }
    }
    else assert(0);
}
int main() {
    for (int i = 1; i <= 20; i++) {
        char filename[100];
        sprintf(filename, "conv%d.in", i);
        freopen(filename, "w", stdout);
        rmain(fn[i], tp[i]);
        fclose(stdout);
    }
}