#include "integer.h"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <random>
namespace integer_grader_F0F01B59EA9BF23E {
	int n, S[1 << 21], p[1 << 21];
	double scoreof(const int x) {
		if(x < 800000) return 1;
		if(x <= 2000000) return 800000.0 / x;
		if(x > 200000000) return 0;
		return (9 - log10(x * 5)) / 5;
	}
	void generateToken()
	{
		unsigned long long Seed = 19260817;
		std::mt19937_64 rng(Seed);
		for(int i = 1; i <= 2333; i++) rng();
		for(int i = 1; i <= 40; i++) printf("%llX", (rng() & 15));
		puts("");
	}
	void quitHalf(const int kth) {
		generateToken();
		puts("WA"), printf("Invalid query: Operation on %d violates range [0,%d]\n", kth, n - 1);
		exit(0);
	}
	int ops, currentPopcnt;
	int operate(const int kth) {
		if(kth < 0 || kth >= n)
			quitHalf(kth);
		currentPopcnt++, S[p[kth]]++, ops--;
		for(int i = p[kth]; S[i] == 2; i++)
			S[i] = 0, S[i + 1]++, currentPopcnt--;
		return currentPopcnt;
	}
	void reportResult(const std::vector<int> &answer) {
		if((int)answer.size() != n)
			puts("WA"), (void)printf("Invalid Answer length: expected %d, found %d\n", n, (int)answer.size()), exit(0);
		ops = -ops;
		for(int i = 0; i < n; i++)
			if(answer[i] != p[i])
				puts("WA"), (void)printf("Incorrect answer: p_%d is expected to be %d but found %d\n", i, p[i], answer[i]), exit(0);
		puts("OK"), (void)printf("Passed using %d operation(s): scoring %.3lf\n", ops, scoreof(ops));
		printf("%.10lf\n", scoreof(ops));
	}
	void main() {
		scanf("%d", &n);
		for(int i = 0; i < n; i++)
			scanf("%d", p + i);
		auto vans = ::findPermutation(n);
		generateToken();
		reportResult(vans);
	}
}
int operate(const int i) {
	return integer_grader_F0F01B59EA9BF23E::operate(i);
}

int main() {
	integer_grader_F0F01B59EA9BF23E::main();
	return 0;
}