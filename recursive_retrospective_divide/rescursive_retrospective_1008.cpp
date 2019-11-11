#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

class Recursive_retrospective{
public:
    Recursive_retrospective() {}

    /*
     * 1
     * 1 2
     * 1 2 3
     * 1 3
     * 2
     * 2 3
     * 3
     */
    void subsetI(vector<int> nums){
        vector<int> item;
        vector<vector<int> > result;

        result.push_back(item);
        generateI(0, nums , item , result);

        /* show resutlt */
        for(int i = 0 ; i < result.size() ; i ++){
            for(int j = 0 ; j < result[i].size() ; j ++){
                cout << result[i][j] << " " ;
            }
            cout << endl;
        }
        return ;

    }
    void generateI(int i , vector<int> &nums, vector<int> &item , vector<vector<int> > &result){
        if(i >= nums.size()) return;
        item.push_back(nums[i]);
        result.push_back(item);
        generateI(i + 1 , nums , item , result);
        item.pop_back();
        generateI(i + 1 , nums , item , result);
    }





    /*
    LeetCode 90.  SubsetsII

    已知一组数(其中有重复元素),求这组数可以组成的所有子集.结果中无重复的子集
    例如: nums[] = [2, 1, 2, 2]
    结果为: [[],[1],[1,2],[1,2,2],[1,2,2,2],[2],[2,2],[2,2,2]]

    注意:[2,1,2]与[1,2,2]是重复的集合

    SampleInput:
        2 1 2 2
    SampleOutput:

        1
        1 2
        1 2 2
        1 2 2 2
        2
        2 2
        2 2 2
    */
    void subSetsII(vector<int> nums){

        vector<int> item;
        vector< vector<int> > result;
        set<vector<int> > res_set;

        sort(nums.begin() , nums.end());
        result.push_back(item);
        generateII(0 , nums , item , result , res_set);

        for(int i = 0 ; i < result.size() ; i ++){
            for(int j = 0 ; j < result[i].size() ; j ++){
                cout << result[i][j] << " " ;
            }
            cout << endl;
        }
        return;
    }
    void generateII(int i , vector<int> &nums , vector<int> &item , vector<vector<int> > &result ,set<vector<int> > &res_set){
        if(i >= nums.size()) return;
        item.push_back(nums[i]);

        if (res_set.find(item) == res_set.end() ) {
            result.push_back(item);
            res_set.insert(item);
        }
        generateII(i + 1 , nums , item , result , res_set);
        item.pop_back();
        generateII(i + 1 , nums , item , result , res_set);

    }

    /*
    LeetCode 40. Combination Sum II

    已知一组数(其中有重复元素),求这组数可以组成的所有子集中,子集中的各个元素和为正号素target的子集,结果中无重复的子集
    SampleInput:
        10 1 2 7 6 1 5
        8
    SampleOutput:
        1 7
        1 2 5
        2 6
        1 1 6
    */

    /*
    在搜索回溯过程中进行剪枝操作:
        递归调用时,计算已选择元素的和sum,若sum > target,不再进行更深的搜索,直接返回
    */
    vector<vector<int> > combinationSum2(vector<int>& candidates, int target) {
        vector<int> item;
        vector<vector<int> > result;
        set<vector<int> > res_set;

        sort(candidates.begin() , candidates.end());
        generateCombSun2(candidates , 0 ,target, item , result,0 ,res_set);

        for(int i = 0 ; i < result.size() ; i++){
            for(int j = 0 ; j < result[i].size() ; j ++){
                cout << result[i][j] << " " ;
            }
            cout << endl;
        }
    }

    void generateCombSun2(vector<int> & nums ,int i, int target , vector<int> &item , vector<vector<int> > &result ,int sum , set<vector<int> > &res_set ){
        if(i >= nums.size() || nums[i] > target) return;
        sum += nums[i];
        item.push_back(nums[i]);
        if(sum == target && res_set.find(item) == res_set.end()){
            result.push_back(item);
            res_set.insert(item);
        }
        generateCombSun2(nums ,i+1, target , item ,result , sum , res_set );
        sum -= nums[i];
        item.pop_back();

        generateCombSun2(nums ,i+1, target , item ,result , sum , res_set );
    }


    /*
    LeetCode 22.

    给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
    例如，给出 n = 3，生成结果为：

    [
      "((()))",
      "(()())",
      "(())()",
      "()(())",
      "()()()"
    ]
    */
   /* all combination of brackets */
   int numOfBrackets(int n){
       vector<string> result;
       generateBrackets("", n ,result);
       for (int i = 0 ; i < result.size() ; i ++)
           cout << result[i] << endl ;
       return 0;
    }

   void generateBrackets(string item , int n , vector<string> &result){
       if(item.size() == 2 * n ){
           result.push_back(item);
           return ;
       }
        generateBrackets(item + "(" + " " , n , result);
        generateBrackets(item + ")" + " " , n , result);
   }



   /* poper brackets */
   int  numPoperBrackets(int n ){
       vector<string> result;
       generateProperBrackets("", n , n , result);
       for (int i = 0 ; i < result.size() ; i ++)
           cout << result[i] << endl ;
       return 0;
   }

   void generateProperBrackets(string item , int left , int right , vector<string> &result){
        if(left == 0 && right == 0){
            result.push_back(item);
            return;
        }
        if(left >0 ){
            generateProperBrackets(item + "(" + " ", left -1 , right  , result);
        }
        if(right > left){
            generateProperBrackets(item + ")" + " ", left  , right - 1 ,result);
        }

   }
};


int main(int argc, char *argv[])
{
    vector<int> vec1 ;
    vec1.push_back(2);
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(2);

    Recursive_retrospective  recu;
//    recu.subsetI(vec1);
//    recu.subSetsII(vec1);

    vector<int> vec2 ;
    vec2.push_back(10);
    vec2.push_back(1);
    vec2.push_back(2);
    vec2.push_back(7);
    vec2.push_back(6);
    vec2.push_back(1);
    vec2.push_back(5);

    recu.combinationSum2(vec2 , 8);

//    recu.numOfBrackets(4);
//    recu.numPoperBrackets(2);
    return 0;
}


