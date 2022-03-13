#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, a[N];
int main(int argc, char* argv[]) {
	registerTestlibCmd(argc, argv);
	string as = ans.readWord();
	string os = ouf.readWord();
	if (as != os) quitf(_wa, "verdict is not correct");
	if (as == "NO") quitf(_ok, "no solution");
	n = inf.readInt();
	m = inf.readInt();
	for (int i = 1; i <= n; i++) a[i] = ouf.readInt(1, 1000000000);
	for (int i = 1; i <= m; i++) {
		int x, y, z, w, t[5];
		x = inf.readInt();
		y = inf.readInt();
		z = inf.readInt();
		w = inf.readInt();
		t[0] = a[x];
		t[1] = a[y];
		t[2] = a[z];
		sort(t, t + 3);
		if (t[1] != w) quitf(_wa, "the %d-th condition is not satisfied", i);
	}
	quitf(_ok, "solution is correct");
	return 0;
}
