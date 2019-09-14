#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
/*
给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

说明：解集不能包含重复的子集。

示例:
输入: [1,2,2]
输出:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector <int> > result;
        vector<int> item;
        vector<vector<int> > res_set;       //去重实现的集合
        sort(nums.begin() , nums.begin());
        result.push_back(item);
        generate(0, nums , result , item , res_set);
    }

private:
    void generate(int i , vector<int> &nums,
                  vector<vector<int> > &result,
                  vector<int> &item,
                  vector<vector<int> > &res_set){
        if (i >= nums.size())
            return;

        item.push_back(nums[i]);

        if(res_set. find(item) == res_set.end()){
            result.push_back(item);
            res_set.insert(item);
        }


        generate(i + 1 , nums , result , item , res_set);
        item.pop_back();
        generate(i + 1 , nums , result , item , res_set);

    }
};
