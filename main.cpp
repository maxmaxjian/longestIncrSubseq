// O(n^2) solution
#include <iostream>
#include <vector>

class solution {
public:
    int lengthOfLIS(const std::vector<int> & nums) {
	int local_maxlen = 1;
	int curr = nums[0];
	for (size_t i = 1; i < nums.size(); i++) {
	    if (nums[i] > curr) {
		local_maxlen++;
		curr = nums[i];
	    }
	}

	size_t i = 1;
	while (i < nums.size() && nums[i] > nums[i-1])
	    i++;
	if (i < nums.size())
	    return std::max(local_maxlen, lengthOfLIS(std::vector<int>(nums.begin()+i, nums.end())));
	else
	    return local_maxlen;
    }
};

int main() {
    std::vector<int> nums{10,9,2,5,3,7,101,18};

    solution soln;
    int maxlen = soln.lengthOfLIS(nums);
    std::cout << "The length of the longest increasing subsequence is:\n"
	      << maxlen << std::endl;
}
