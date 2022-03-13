#include "integer.h"
#include <vector>
std::vector<int> findPermutation (int n) {
	std::vector<int> ans;
	for(int i=0; i<n; i++)
		ans.push_back(i);
	return ans;
}