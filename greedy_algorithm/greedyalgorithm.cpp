#include "greedyalgorithm.h"

Greedyalgorithm::Greedyalgorithm()
{

}

/*
LeetCode 455 Assign Cookies



已知一些孩子和一些糖果，每个孩子有需求因子g，每个糖果有大小 s，当某个糖果的大小 s >= 某个孩子的需求因子 g 时，代表该糖果可以满足该孩子；
求使用这些糖果，最多能满足多少孩子？(注意，某个孩子最多只能用1个糖果满足)。

For example:
        需求因子数组 g = [5, 10, 2, 9, 15, 9]；
        糖果大小数组 s = [6, 1, 20, 3, 8]；
    最多可以满足3个孩子。

SampleInput:
    5 10 2 9 15 9
    6 1 20 3 8

SampleOutput:
    3
*/

/*
Thinking:

For example, an array of demand factors: g = [5, 10, 2, 9, 15, 9]; an array of candy sizes: s = [6, 1, 20, 3, 8];
In order to  judge that a child can be satisfied by a candy more clearly, sort the g, s and observe:
    g = [2,5,9,9,10,15];
    s = [1,3,6,8,20].

1. When a child can be satisfied by multiple candy, is it necessary to give priority to him with a candy?
2. When a candy can satisfy multiple children, is it necessary to give priority to a child?


核心目标:让更多的孩子得到满足,有如下规律:
1.某个糖果不能满足某个孩子,则该糖果也一定不能满足需求因子更大的孩子
如:
    s=1 不能满足孩子 g=2,则不能满足孩子2,3,4,..,7
    s=3 不能满足孩子 g=5,则不能满足孩子3,4,...,7

2.当某个孩子可以用更小的糖果满足时,则没必要更大糖果满足,因此可以保留更大的糖果满足需求因子更大的孩子(贪心)
如:
    g=2,可以被s=3满足,则没必要用s=6,8等满足;
    g=5,可以被s=6满足,则没必要用s=8,20满足;

3.孩子的需求因子更小则其更容易被满足,故优先从需求因子小的孩子尝试.
*/

int Greedyalgorithm::assignCandies(){
    vector<int> g ;         //vector to save children
    vector<int> s ;         //vector to save candies


    /* input original data */
    int tem_g;
    while (1) {
        cin >> tem_g;
        g.push_back(tem_g);
        if(cin.get() == '\n')
            break;
    }

    int tem_s;
    while (1) {
        cin >> tem_s;
        s.push_back(tem_s);
        if(cin.get() == '\n')
            break;
    }

    /* greedy algorithm opreation */
    std::sort(g.begin() , g.end());
    std::sort(s.begin() , s.end());

    int i_g = 0 , i_s = 0;  //two indexes to point to each element in g and s
    while (i_g < g.size() && i_s < s.size()) {
        if( g[i_g] <= s[i_s]){
            i_g ++ ;
        }
        i_s ++;
    }
    return i_g ++;
}


/*
LeetCode 376. Wiggle Subsequence

A sequence of numbers is called a wiggle sequence if the differences between successive numbers strictly alternate between positive and negative.
 The first difference (if one exists) may be either positive or negative. A sequence with fewer than two elements is trivially a wiggle sequence.

For example, [1,7,4,9,2,5] is a wiggle sequence because the differences (6,-3,5,-7,3) are alternately positive and negative.
In contrast, [1,4,7,2,5] and [1,7,4,5,5] are not wiggle sequences,
the first because its first two differences are positive and the second because its last difference is zero.

Given a sequence of integers, return the length of the longest subsequence that is a wiggle sequence.
A subsequence is obtained by deleting some number of elements (eventually, also zero) from the original sequence,
leaving the remaining elements in their original order.


一个整数序列，如果两个相邻元素的差恰好正负(负正)交替出现，则该序列被称为摇摆序列。一个小于2个元素的序列直接为摇摆序列。

例如:序列[1, 7, 4, 9, 2, 5]，相邻元素的差(6, -3, 5, -7, 3)，该序列为摇摆序列。
序列[1,4,7,2,5](3, 3, -5, 3)、[1,7,4,5,5] (6, -3, 1, 0)不是摇摆序列。
给一个随机序列，求这个序列满足摇摆序列定义的最长子序列的长度。

例如:输入[1,7,4,9,2,5]，结果为6；输入[1,17,5,10,13,15,10,5,16,8]，结果为7([1,17,10,13,10,16,8] )；输入[1,2,3,4,5,6,7,8,9]，结果为2。

Sample Input:
    1 7 4 9 2 5

    1 17 5 10 13 15 10 5 16 8

    1 2 3 4 5 6 7 8 9

Sample Output:
    6

    7

    2
*/


/*
思考

观察[1 17 5 10 13 15 10 5 16 8]   整体不是摇摆序列:

观察该序列前 6 位[1 17 5 10 13 15 ...],发现其[5 10 13 15]位上升段
其中它有3个子序列时摇摆序列
1 17 5 10 ...
1 17 5 13 ...
1 17 5 15 ...

在不清楚原始序列的 7 位是什么的情况下,只看前6位,摇摆子序列的第四位从10,13,15中选择一个数
那么我们选哪个好?

目标:成为摇摆子序列的下一个元素的概率更大,摇摆子序列长度 ++
第4位选择最大的15
更可能使得原始第 7 位成为摇摆序列的下一个元素


当序列有一段连续二点递增(或递减)时,为形成摇摆子序列,我们只需要保留这段连续的递增(递减)的首尾元素,
这样更可能使得尾部的后一个元素成为摇摆子序列的下个元素.
*/
int Greedyalgorithm::wiggleSubsequence(){
    vector<int> nums;

    /* input data */
    int tem;
    while (1) {
        cin >> tem;
        nums.push_back(tem);
        if (tem == '\n')    break;
    }

    if(nums.size() < 2)     //序列小于2时直接为摇摆序列
        return nums.size();

    /* 扫描序列时的三种状态 */
    static const int BEGIN = 0;
    static const int UP = 1;
    static const int DOWN = 2;
    int STATE = BEGIN;
    int max_length = 1 ;    //扫描序列最大长度至少为1

    /* 从第二个元素开始扫描 */
    for (int i = 1 ; i < nums.size() ; i ++){
        switch (STATE) {
        case BEGIN:
            if(nums[i - 1] < nums[i]){
                STATE = UP;
                max_length ++;
            }
            else if(nums[i - 1] > nums[i]){
                STATE = DOWN;
                max_length ++;
            }
            break;
        case UP:
            if(nums[i - 1] > nums[i]){
                STATE = DOWN;
                max_length ++;
            }
            break;
        case DOWN:
            if(nums[i - 1] < nums[i]){
                STATE = UP;
                max_length ++;
            }
            break;
        }

    }
    return max_length;

}


/*
LeetCode 402. Remove K Digits
移除k个数字
已知一个使用字符串表示的非负整数num，将num中的k个数字移除， 求移除k个数字后，可以获得的最小的可能的新数字。(num不会以0开头,num长度小于10002)
如输入 : num = “1432219” , k = 3
在去掉3个数字后得到的很多很多可能里，如1432、4322、2219、1219、 1229...;去掉数字4、3、2得到的1219最小!

Sample Input
    1432219 3
Sample Ouput
    1219

*/

/*
思路:

从高位向低位遍历,如果对应的数字大于下一位数字,则把该位数字去掉,得到的数字最小!
最暴力的方法: 去掉k个数字,即从最高位遍历k次

使用栈存储最终结果或删除工作,从高位向低位遍历num,
如果遍历的数字大于栈顶元素,则将该数字push入栈,
如果小于栈顶元素则pop出栈,直到栈为空或不能再删除数字(k == 0)或栈顶小于当前元素为止.

思考下列问题:
1.当所有的数字都扫描完成后,k仍然 > 0 ,应该做怎样的处理?
    例如:num = 12345 , k = 3 时

2.当数字中有0出现时,应该有怎样的特殊处理?
    例如:num = 100200, k = 1 时

3.如何将最后结果存储为字符串并返回?
*/

string Greedyalgorithm::removeKdigits(){
    string num;
    int k;
    cin >> num >> k;

    vector<int> S;                                  //使用vector当栈(因为vector可以遍历)
    string result = "";                             //存储最终结果的字符串
    for(int i = 0; i < num.length() ; i ++){        //从最高位循环扫描数字
        int number = num[i] - '0';                  //将字符型的num转换为int型
        while (S.size() != 0 &&   S[S.size() - 1] > number && k > 0 ) {
            S.pop_back();                           //pop the top of stack
            k--;
        }
        if(number != 0 || S.size() !=0) {
            S.push_back(number);
        }
    }
    while(S.size() != 0  && k > 0){
        S.pop_back();
        k--;
    }

    /* save the element from vector */
    for(int i = 0 ; i < S.size() ; i++)
        result.append(1,'0' + S[i]);
    if(result == ""){
        result = "0";
    }
    return result;
}

/*
LeetCode 55. JumpGame

题目描述

给定一个非负整数数组，你最初位于数组的第一个位置。数组中的每个元素代表你在该位置可以跳跃的最大长度。判断你是否能够到达最后一个位置。

示例 1:

Sample Input
    2 3 1 1 4
Sample Output
    true

解释: 从位置 0 到 1 跳 1 步, 然后跳 3 步到达最后一个位置。

示例 2:

输入: 3 2 1 0 4
输出: false

解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ， 所以你永远不可能到达最后一个位置。
*/

/*
思考:

从第i个位置,最远可跳nums[i]步:nums = [2,3,1,1,4,...];
从第i个位置,最远可跳至第index[i]个位置:  设index[i]存放的是在原始中第i个位置能跳的最远位置
index[i] = i + nums[i];
index = [2,4,3,4,8,...]

若从第0位置最远可以跳至第i个位置;
则从第0位置也一定可以跳至:
    第1个,第2个,...第i-1个位置
那么从第0个位置,应该跳至第1个,第2个,...第i-1,第i个位置中的哪个?
    应该跳至第1,2,...i-1,i位置中,又可向前跳至更远位置
    [即index[1],index[2],...,index[i-1],index[i]最大的那个的位置(贪心)]


思路:
1.求从第i位置最远可跳至第index[i]位置:
    根据从第i位置最远可跳nums[i]步: index = nums[i] + i ;
2.初始化:
    a.设置变量jump代表当前所处位置,初始化为0;
    b.设置变量max_index代表从第0位置至jump位置这个过程中,最远可到达的位置,出书啊为index[0]
3.利用jump扫描index数组,直到jump达到index数组尾部或jump超过max_index.扫描过程中,更新max_index.
4.若最终jump为数组长度,则返回true,否则返回false.
*/
bool Greedyalgorithm::canJump(){
    vector<int> nums;       //to save the origin data
    vector<int> index;      //index[i] shows the ith data in nums that can reach the position in nums

    /* input datas */
    int tem = 0;
    while (1) {
        cin >> tem;
        nums.push_back(tem);
        if (tem == '\n') break;
    }
    for(int i = 0 ; i < nums.size() ; i ++){
        index.push_back(i + nums[i]);
    }
    int jump = 0;
    int max_index = index[0];
    while ( jump < index.size() && jump <= max_index ) {
        if(max_index < index[jump]){
               max_index = index[jump];
        }
        jump ++ ;
    }
    if(max_index >= index.size())            //jump has reach the end of index array
        return true;
    return false;

}
