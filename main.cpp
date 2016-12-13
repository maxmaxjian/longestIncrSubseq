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

// // O(n^2) solution
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <iterator>
// #include <unordered_map>

// namespace std {
//     std::ostream & operator<<(std::ostream & os, const std::pair<size_t, int> & p) {
//         os << p.first << " -> " << p.second;
//         return os;
//     }
// }

// class solution {
//   public:
//     int lengthOfLIS(const std::vector<int> & nums) {
//         // auto cpy = nums;
//         // std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, " "));
//         // std::cout << std::endl;
//         // auto it = std::stable_partition(cpy.begin()+1, cpy.end(),
//         //                       [&](int i){
//         //                           return i < cpy[0];
//         //                       });
//         // std::copy(cpy.begin(), cpy.end(), std::ostream_iterator<int>(std::cout, " "));
//         // std::cout << std::endl;
//         // std::cout << "Starting from " << *it << std::endl;
//         // return 0;


//         std::vector<int> cands;
//         for (size_t i = 0; i < nums.size(); i++)
//             if (std::all_of(dict.begin(), dict.end(), [&](const std::pair<size_t,int> & p){return nums[i] < nums[p.first];})) {
//                 std::cout << i << std::endl;
//                 // dict.insert(std::make_pair(i, lengthFrom(nums, i)));
//                 cands.push_back(lengthFrom(nums, i));
//             }

//         // std::copy(dict.begin(), dict.end(), std::ostream_iterator<std::pair<size_t,int>>(std::cout, "\n"));
        
//         // auto it = std::max_element(dict.begin(), dict.end(),
//         //                            [](const std::pair<size_t,int> & p1, const std::pair<size_t,int> & p2){return p1.second < p2.second;});
//         // return it->second;
//         return *std::max_element(cands.begin(), cands.end());
//     }

//   private:
//     int lengthFrom(const std::vector<int> & nums, size_t start) {
//         if (dict.find(start) == dict.end()) {
//             int len = 0;
//             if (start == nums.size()-1)
//                 len = 1;
//             else if (start < nums.size()-1){
//                 std::vector<int> vec;
//                 for (size_t i = start+1; i < nums.size(); i++)
//                     if (nums[i] > nums[start])
//                         vec.push_back(lengthFrom(nums, i)+1);
//                 if (!vec.empty())
//                     len = *std::max_element(vec.begin(), vec.end());
//                 else
//                     len = 1;
//             }
//             dict[start] = len;
//         }
//         return dict[start];
//     }

//   private:
//     std::unordered_map<size_t,int> dict;
// };

// O(nlog(n)) solution
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

namespace std {
    std::ostream & operator<<(std::ostream & os, const std::vector<int> & v) {
        std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
        return os;
    }
}

class solution {
  public:
    int lengthOfLIS(const std::vector<int> & nums) {
        std::vector<std::vector<int>> vecs;
        for (auto & n : nums) {
            if (vecs.empty()) {
                vecs.push_back(std::vector<int>{n});
            }
            else {
                if (std::all_of(vecs.begin(), vecs.end(), [&](const std::vector<int> & v){return v.back() > n;})) {
                    vecs.push_back(std::vector<int>{n});
                }
                else if (std::all_of(vecs.begin(), vecs.end(), [&](const std::vector<int> & v){return v.back() < n;})) {
                    auto it = std::max_element(vecs.begin(), vecs.end(), [](const std::vector<int> & v1, const std::vector<int> & v2){return v1.size() < v2.size();});
                    auto temp = *it;
                    temp.push_back(n);
                    vecs.emplace_back(std::move(temp));
                }
                else {
                    auto it = vecs.begin();
                    while (it != vecs.end() && it->back() > n)
                        ++it;
                    auto curr = std::next(it);
                    while (curr != vecs.end()) {
                        if (curr->back() < n && curr->size() > it->size())
                            it = curr;
                        ++curr;
                    }

                    it->push_back(n);
                    
                    size_t len = it->size();
                    auto jt = vecs.begin();
                    while (jt != vecs.end()) {
                        if (jt != it && jt->size() == len)
                            jt = vecs.erase(jt);
                        else
                            ++jt;
                    }
                }
            }
            // std::copy(vecs.begin(), vecs.end(), std::ostream_iterator<std::vector<int>>(std::cout, "\n"));
            // std::cout << std::endl;
        }        

        std::cout << "One of the longest increasing subsequences is:\n";
        auto it = std::max_element(vecs.begin(), vecs.end(), [](const std::vector<int> & v1, const std::vector<int> & v2){return v1.size() < v2.size();});        
        std::copy(it->begin(), it->end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        
        return it->size();
    }
};

// #include <iostream>
// #include <vector>
// #include <climits>
// #include <utility>
// #include <algorithm>
// #include <iterator>

// class solution {
//   public:
//     int lengthOfLIS(const std::vector<int> & nums) {
//         std::vector<std::vector<std::pair<int,int>>> piles;
//         for (auto n : nums) {
//             if (piles.empty()) {
//                 piles.push_back(std::vector<std::pair<int,int>>{std::make_pair(INT_MIN,n)});
//             }
//             else {
//                 auto it = piles.begin();
//                 while (it != piles.end() && it->back().second < n)
//                     ++it;
//                 if (it == piles.end()) {
//                     piles.push_back(std::vector<std::pair<int,int>>{std::make_pair(std::prev(it)->back().second,n)});
//                 }
//                 else {
//                     if (it == piles.begin())
//                         it->push_back(std::make_pair(INT_MIN, n));
//                     else                       
//                         it->push_back(std::make_pair(std::prev(it)->back().second, n));
//                 }
//             }
//         }

//         std::vector<int> lis;
//         auto it = piles.rbegin();
//         int next = it->back().second;
//         while (it != piles.rend()) {
//             auto ite = std::find_if(it->begin(), it->end(), [&](const std::pair<int,int> & p){ return p.second == next;});
//             lis.push_back(next);
//             ++it;
//             next = ite->first;
//         }
//         std::copy(lis.rbegin(), lis.rend(), std::ostream_iterator<int>(std::cout, " "));
//         std::cout << std::endl;

//         return piles.size();
//     }
// };

int main() {
    // std::vector<int> nums{10,9,2,5,3,7,101,18};
    std::vector<int> nums{6,3,5,10,11,2,9,14,13,7,4,8,12};

    solution soln;
    int maxlen = soln.lengthOfLIS(nums);
    std::cout << "The length of the longest increasing subsequence is:\n"
	      << maxlen << std::endl;
}
