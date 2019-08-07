#include "recursive_retrospective.h"

Recursive_retrospective::Recursive_retrospective(){

}


/*
LeetCode 78,Subsets

已知一组数(其中无重复元素),求这组数可以组成的所有子集
结果中不可有无重复的子集

例如: 输入: 1 2 3
结果为: [[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]]
*/

/*
在所有子集中,生成各个子集, [[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]]
即是选[1],是否选[2],是否选[3]的问题

如果只使用循环,困难在哪里?
使用循环难以直接模拟是否选某一元素的过程

如果只是生成[1],[1,2],[1,2,3]三个子集,如何做?
*/
void Recursive_retrospective::subSets(){
    vector<int> nums;

    int tem;
    while(1){
        cin >> tem;
        nums.push_back(tem);
        if( cin.get() == '\n')  break;
    }

    vector<int> item;           //item, 生成各个子集的数组
    vector<vector<int>> result; //result,最终结果数组


    result.push_back(item);     //push empty set in
    generate(0 , nums, item , result);


    for(int i = 0 ; i < result.size() ; i ++){
        for(int j = 0 ; j < result[i].size() ; j ++){
            cout << result[i][j] << " " ;
        }
        cout << endl;
    }
    return ;
}

void generate(int i, vector<int>& nums, vector<int> &item, vector<vector<int>> &result){



    if(i >= nums.size())
        return;
    item.push_back(nums[i]);
    result.push_back((item));
    generate(i + 1,nums,item,result);

    item.pop_back();
    generate(i + 1, nums, item, result);
}


/*

*/
