#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
/*
����һ�����ܰ����ظ�Ԫ�ص��������� nums�����ظ��������п��ܵ��Ӽ����ݼ�����

˵�����⼯���ܰ����ظ����Ӽ���

ʾ��:
����: [1,2,2]
���:
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
        vector<vector<int> > res_set;       //ȥ��ʵ�ֵļ���
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
