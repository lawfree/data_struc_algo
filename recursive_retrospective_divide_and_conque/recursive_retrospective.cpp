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


/*
有两种重复的原因:
1.不同位置的元素组成的集合是同一个子集,顺序相同:
例如:2 1 2 2
    选择第1,2,3个元素组成的子集:2,1,2
    选择第1,2,4个元素组成的子集:2,1,2

2.不同位置的元素组成的集合是同一个子集,顺序不同,但仍然代表了同一个子集,因为集合中的元素是无序的
例如:2 1 2 2
    选择1,2,3个元素组成的子集:2,1,2
    选择2,3,4个元素组成的子集:1,2,2

不同位置的元素组成的集合是同一个子集,子集的各个元素顺序相同,或顺序不同,解决办法

解决方案:
先对原始nums数组进行排序,再使用set去重
例如: 2 1 2 2 排序后:1 2 2 2
无论如何选,均只出现1 2 2
*/
void Recursive_retrospective::subSetsII(){
    vector<int> nums;
    int tem = 0;
    while (1) {
        cin >> tem;
        nums.push_back(tem);
        if (cin.get() == '\n') break;
    }

    vector< vector<int> > result;
    vector<int> item;
    set< vector<int> > res_set;         //remove duplicate set
    sort(nums.begin() , nums.end());    //sort to nums
    result.push_back(item);
    generateII(0,nums,result , item , res_set);
}
void generateII(int i, vector<int>& nums,  vector<vector<int>> &result,vector<int> &item, set<vector<int> > &res_set){
    if (i >= nums.size() )
        return;
    item.push_back(nums[i]);
    if(res_set.find(item) == res_set.end()){    //if can't find item in res_set
        result.push_back(item);     //put item to result
        res_set.insert(item);
    }
    generateII(i + 1, nums , result , item , res_set);
    item.pop_back();
    generateII(i + 1, nums, result ,item, res_set);

    for(int i = 0 ; i < result.size() ; i ++){
        for(int j = 0 ; j < result[i].size() ; j ++){
            cout << result[i][j] << " " ;
        }
        cout << endl;
    }
    return ;
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

/* we can print all combination of brackets */
int Recursive_retrospective::numOfBrackets(){
    int n = 0;
    cin >> n;

    vector<string> result;
    generateBracket("", n ,result);
    for (int i = 0 ; i < result.size() ; i ++)
        cout << result[i] << endl ;
    return 0;
}
int generateBracket(string item, int n, vector<string> &result ){
    if(item.size() == 2 * n){
        result.push_back(item);
        return 0;
    }
    generateBracket(item + '(' + " " , n , result);
    generateBracket(item + ')' + " " , n , result);

}

/*
在组成的所有可能中,哪些是合法的?
    1.左括号与右括号的数量不可超过n
    2.每放一个左括号,才可以放一个右括号,即右括号不能先于左括号位置
故递归需要限制条件:
    1.左括号与右括号的数量,最多放置n个
    2.若左括号的数量 <= 右括号数量,不可进行放置右括号的递归

*/

int Recursive_retrospective::numOfCombBrackets(){
    int n;
    cin >> n;

    vector<string> result;
    generateCombBracket("", n , n ,result);
    for (int i = 0 ; i < result.size() ; i ++)
        cout << result[i] << endl ;

    return 0;
}
int generateCombBracket(string item , int left , int right , vector<string> &result){
    if( left == 0 && right ==0  ){
        result.push_back(item);
        return 0;
    }
    if(left > 0){
        generateCombBracket(item +  '(' , left - 1 , right -1 ,result);
    }
    if( left < right )
        generateCombBracket(iten + ')' , left , right - 1 ,result);
}

/*
LeetCode 51. n-queens

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,

There exist two distinct solutions to the 4-queens puzzle:

    [
     [".Q..",  // Solution 1
      "...Q",
      "Q...",
      "..Q."],

     ["..Q.",  // Solution 2
      "Q...",
      "...Q",
      ".Q.."]
    ]
*/
void put_down_the_queen(int x , int y , vector< vector<int> > &mark){

    static const int dx[] = {-1,1, 0 ,0 , -1, -1, 1 , 1};
    static const int dx[] = {0 ,0, -1,1 , -1,  1, -1, 1};

    mark[x][y] = 1 ; //(x, y) set queen and mark it
    for(int i = 1 ; i < mark.size() ; i ++){
        for(int j = 1 ; j < mark.size() ; j ++){
            int new_x = x + i * dx[j];
            int new_y = y + i * dy[j];
            if(new_x >= 0 && new_x < mark.size() && new_y >= 0 && new_y < mark.size())
                mark[new_x][new_y] = 1;
        }
    }
}

/*
N皇后问题,对于N*N的棋盘,每行都要放置一个且只能放置一个皇后
利用递归对棋盘的每一行放置皇后,放置时,按列顺序寻找可以放置皇后的列,若可以放置皇后,放皇后于该位置,并更新mark标记数组,
递归进行下一行的皇后放置位置;
当该次递归结束后,恢复mark数组,并尝试下一个可能放皇后的列.
当递归可以完成N行的N个皇后放置,则将该结果保存并返回.
*/
vector<vector <string>> solveNQueens(int n){
    vector<vector<string> > result;             //save the end result;
    vector<vector<int> > mark;                  //mark if could set queen
    vector<std::string> location;                    //save a result,when finishing a time,put location to result

    for(int i = 0 ; i < n ; i ++){
        mark.push_back(vector <int> ());
        for(int j = 0 ; j < n ; j ++){
            mark[i].push_back(0);
        }
        location.push_back("");
        location[i].append(n , '.');
    }
    generateNQueens(0, n , location , result , mark);
    return result;
}
void generateNQueens(int k , int n ,
                     vector<string> &location ,
                     vector<vector<string> > &result ,
                     vector<vector <int> >  &mark){

}
