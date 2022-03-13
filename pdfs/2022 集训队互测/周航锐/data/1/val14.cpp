#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main() {
	registerValidation();
	int n = inf.readInt(1, 8, "n");
	inf.readEoln();
	int m = 1, d = 1;
	for (int i = 0; i < n; i++) d *= 6;
	for (int i = 1; i <= d; i++) {
		int c = inf.readInt(0, 998244352, "c");
		m = (m + c) % 998244353;
		if (i != d) inf.readSpace();
		else inf.readEoln();
	}
	ensuref(m != 0, "m is multiple of mod");
    inf.readEof();
}