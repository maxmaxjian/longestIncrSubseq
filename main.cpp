// // O(n^2) solution
// #include <iostream>
// #include <vector>

// class solution {
// public:
//     int lengthOfLIS(const std::vector<int> & nums) {
// 	int local_maxlen = 1;
// 	int curr = nums[0];
// 	for (size_t i = 1; i < nums.size(); i++) {
// 	    if (nums[i] > curr) {
// 		local_maxlen++;
// 		curr = nums[i];
// 	    }
// 	}

// 	size_t i = 1;
// 	while (i < nums.size() && nums[i] > nums[i-1])
// 	    i++;
// 	if (i < nums.size())
// 	    return std::max(local_maxlen, lengthOfLIS(std::vector<int>(nums.begin()+i, nums.end())));
// 	else
// 	    return local_maxlen;
//     }
// };

// // O(n^2)) solution
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <iterator>

// class solution {
//   public:
//     int lengthOfLIS(const std::vector<int> & nums) {
//         std::vector<std::vector<size_t>> seqs;
//         for (size_t i = 0; i < nums.size(); i++) {
//             auto seq = grow(nums, std::vector<size_t>{i});
//             std::copy(seq.begin(), seq.end(), std::inserter(seqs, seqs.end()));
//         }

//         auto it = std::max_element(seqs.begin(), seqs.end(),
//                                    [](const std::vector<size_t> & v1, const std::vector<size_t> & v2){
//                                        return v1.size() < v2.size();
//                                    });
//         std::for_each(it->begin(), it->end(), [&](size_t idx){
//             std::cout << nums[idx] << " ";
//         });
//         std::cout << std::endl;
        
//         return it->size();
//     }

//   private:
//     std::vector<std::vector<size_t>> grow(const std::vector<int> & nums, const std::vector<size_t> & curr) {
//         std::vector<std::vector<size_t>> result;
//         std::vector<size_t> next = getNext(nums, curr);
//         if (next.empty())
//             result.push_back(curr);
//         else {
//             for (auto & nx : next) {
//                 auto cpy = curr;
//                 cpy.push_back(nx);
//                 auto temp = grow(nums, cpy);
//                 std::copy(temp.begin(), temp.end(), std::inserter(result, result.end()));
//             }
//         }
//         return result;
//     }

//     std::vector<size_t> getNext(const std::vector<int> & nums, const std::vector<size_t> & curr) {
//         std::vector<size_t> next;
//         for (size_t i = curr.back()+1; i < nums.size(); ++i) {
//             if (nums[i] > nums[curr.back()])
//                 next.push_back(i);
//         }
//         return next;
//     }
// };

// O(nlog(n)) solution
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>

namespace std {
    std::ostream & operator<<(std::ostream & os, const std::pair<size_t, int> & p) {
        os << p.first << " -> " << p.second;
        return os;
    }
}

class solution {
  public:
    int lengthOfLIS(const std::vector<int> & nums) {
        // auto cpy = nums;
        // std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, " "));
        // std::cout << std::endl;
        // auto it = std::stable_partition(cpy.begin()+1, cpy.end(),
        //                       [&](int i){
        //                           return i < cpy[0];
        //                       });
        // std::copy(cpy.begin(), cpy.end(), std::ostream_iterator<int>(std::cout, " "));
        // std::cout << std::endl;
        // std::cout << "Starting from " << *it << std::endl;
        // return 0;


        for (size_t i = 0; i < nums.size(); i++)
            if (std::all_of(dict.begin(), dict.end(), [&](const std::pair<size_t,int> & p){return nums[i] < nums[p.first];}))
                dict.insert(std::make_pair(i, lengthFrom(nums, i)));

        std::copy(dict.begin(), dict.end(), std::ostream_iterator<std::pair<size_t,int>>(std::cout, "\n"));
        
        auto it = std::max_element(dict.begin(), dict.end(), [](const std::pair<size_t,int> & p1, const std::pair<size_t,int> & p2){return p1.second < p2.second;});
        return it->second;
    }

  private:
    int lengthFrom(const std::vector<int> & nums, size_t start) {
        if (dict.find(start) == dict.end()) {
            int len = 0;
            if (start == nums.size()-1)
                len = 1;
            else if (start < nums.size()-1){
                std::vector<int> vec;
                for (size_t i = start+1; i < nums.size(); i++)
                    if (nums[i] > nums[start])
                        vec.push_back(lengthFrom(nums, i)+1);
                if (!vec.empty())
                    len = *std::max_element(vec.begin(), vec.end());
                else
                    len = 1;
            }
            dict[start] = len;
        }
        return dict[start];
    }

  private:
    std::unordered_map<size_t,int> dict;
};

int main() {
    std::vector<int> nums{10,9,2,5,3,7,101,18};

    solution soln;
    int maxlen = soln.lengthOfLIS(nums);
    std::cout << "The length of the longest increasing subsequence is:\n"
	      << maxlen << std::endl;
}
