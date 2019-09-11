#include<stdio.h>

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/*
LeetCode 78.  Subsets


给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

说明：解集不能包含重复的子集。

示例:

输入: nums = [1,2,3]
输出:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]

*/


/*
vector<int> item                //item      generate vector of each subset
vector<vector<int> >  result    //result    save the end result
*/
class Solution {
public:
    vector<vector<int> > subsets(vector<int>& nums) {

        vector<int> item;
        vector<vector <int> > result;
        result.push_back(item);     // do not forget empty set
        generate_2(0 , nums , item , result);

         return result;
    }

    /* prepare knowlagde */
    /*
        1
        1 2
        1 2 3
    */
    void generate_1(int i , vector<int>& nums ,vector<int >& item,vector<vector<int> >& result){
        if( i >= nums.size() )
            return;
        item.push_back(nums[i]);
        result.push_back(item);

        generate_1(i + 1 , nums ,item , result);

    }

private:
    /* solove the program */
    /*
        1
        1 2
        1 2 3
        1 3
        2
        2 3
        3

    */
    void generate_2(int i , vector<int>& nums ,vector<int >& item,vector<vector<int> >& result){
        if(i >= nums.size())
            return;

        item.push_back(nums[i]);
        result.push_back(item);
        generate_2(i  + 1 , nums , item , result);
        item.pop_back();
        generate_2(i  + 1 , nums , item , result);

    }
};

int main(int argc, char *argv[])
{
    vector<int> nums ;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);

    vector<int> item;
    vector<vector <int> > result;

    Solution so;
//    so.generate_1(0 , nums , item , result);
    result =  so.subsets(nums);

    for(int i = 0 ; i < result.size() ; i ++){

        for(int j = 0 ; j < result[i].size() ; j ++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

