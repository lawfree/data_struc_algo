#include "recursive_retrospective.h"

Recursive_retrospective::Recursive_retrospective(){

}


/*
LeetCode 78,Subsets

��֪һ����(�������ظ�Ԫ��),��������������ɵ������Ӽ�
����в��������ظ����Ӽ�

����: ����: 1 2 3
���Ϊ: [[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]]
*/

/*
�������Ӽ���,���ɸ����Ӽ�, [[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]]
����ѡ[1],�Ƿ�ѡ[2],�Ƿ�ѡ[3]������

���ֻʹ��ѭ��,����������?
ʹ��ѭ������ֱ��ģ���Ƿ�ѡĳһԪ�صĹ���

���ֻ������[1],[1,2],[1,2,3]�����Ӽ�,�����?
*/
void Recursive_retrospective::subSets(){
    vector<int> nums;

    int tem;
    while(1){
        cin >> tem;
        nums.push_back(tem);
        if( cin.get() == '\n')  break;
    }

    vector<int> item;           //item, ���ɸ����Ӽ�������
    vector<vector<int>> result; //result,���ս������


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

��֪һ����(�������ظ�Ԫ��),��������������ɵ������Ӽ�.��������ظ����Ӽ�
����: nums[] = [2, 1, 2, 2]
���Ϊ: [[],[1],[1,2],[1,2,2],[1,2,2,2],[2],[2,2],[2,2,2]]

ע��:[2,1,2]��[1,2,2]���ظ��ļ���

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
�������ظ���ԭ��:
1.��ͬλ�õ�Ԫ����ɵļ�����ͬһ���Ӽ�,˳����ͬ:
����:2 1 2 2
    ѡ���1,2,3��Ԫ����ɵ��Ӽ�:2,1,2
    ѡ���1,2,4��Ԫ����ɵ��Ӽ�:2,1,2

2.��ͬλ�õ�Ԫ����ɵļ�����ͬһ���Ӽ�,˳��ͬ,����Ȼ������ͬһ���Ӽ�,��Ϊ�����е�Ԫ���������
����:2 1 2 2
    ѡ��1,2,3��Ԫ����ɵ��Ӽ�:2,1,2
    ѡ��2,3,4��Ԫ����ɵ��Ӽ�:1,2,2

��ͬλ�õ�Ԫ����ɵļ�����ͬһ���Ӽ�,�Ӽ��ĸ���Ԫ��˳����ͬ,��˳��ͬ,����취

�������:
�ȶ�ԭʼnums�����������,��ʹ��setȥ��
����: 2 1 2 2 �����:1 2 2 2
�������ѡ,��ֻ����1 2 2
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

��֪һ����(�������ظ�Ԫ��),��������������ɵ������Ӽ���,�Ӽ��еĸ���Ԫ�غ�Ϊ������target���Ӽ�,��������ظ����Ӽ�
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
���������ݹ����н��м�֦����:
    �ݹ����ʱ,������ѡ��Ԫ�صĺ�sum,��sum > target,���ٽ��и��������,ֱ�ӷ���
*/


/*
LeetCode 22.

���� n �����������ŵĶ���������д��һ��������ʹ���ܹ��������п��ܵĲ�����Ч��������ϡ�
���磬���� n = 3�����ɽ��Ϊ��

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
����ɵ����п�����,��Щ�ǺϷ���?
    1.�������������ŵ��������ɳ���n
    2.ÿ��һ��������,�ſ��Է�һ��������,�������Ų�������������λ��
�ʵݹ���Ҫ��������:
    1.�������������ŵ�����,������n��
    2.�������ŵ����� <= ����������,���ɽ��з��������ŵĵݹ�

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

The n-queens puzzle is the problem of placing n queens on an n��n chessboard such that no two queens attack each other.

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
N�ʺ�����,����N*N������,ÿ�ж�Ҫ����һ����ֻ�ܷ���һ���ʺ�
���õݹ�����̵�ÿһ�з��ûʺ�,����ʱ,����˳��Ѱ�ҿ��Է��ûʺ����,�����Է��ûʺ�,�Żʺ��ڸ�λ��,������mark�������,
�ݹ������һ�еĻʺ����λ��;
���ôεݹ������,�ָ�mark����,��������һ�����ܷŻʺ����.
���ݹ�������N�е�N���ʺ����,�򽫸ý�����沢����.
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
