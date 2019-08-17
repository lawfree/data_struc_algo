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
        if (cin.get() == '\n')    break;
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

i:          0 1 2 3 4 5 6 7
nums[i]:    1 2 3 0 0 0 0 5
index[i]:   1 3 5 3 4 5 6 12


*/
bool Greedyalgorithm::canJump(){
    vector<int> nums;       //to save the origin data
    vector<int> index;      //index[i] shows the ith data in nums that can reach the position in nums

    /* input datas */
    int tem ;
    while (1) {
        cin >> tem;
        if (cin.get() == '\n') break;
        nums.push_back(tem);       
    }

    for(int i = 0 ; i < nums.size() ; i ++){
        index.push_back(i + nums[i]);
    }
    int jump = 0;
    int max_index = index[0];
    while ( jump < index.size() && jump <= max_index ) {  //max_index is changing,for example, in index[i]:   1 3 5 3 4 5 .. there must be a num bigger than 5
        if(max_index < index[jump]){
               max_index = index[jump];
        }
        jump ++ ;
    }
    if(jump == index.size())            //jump has reach the end of index array
        return true;
    return false;
}

/*
LeetCode 55. JumpGame 2

 Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Your goal is to reach the last index in the minimum number of jumps.
For example:

Given array A = [2,3,1,1,4]
The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)

Sample Input:
    2 3 1 1 4
Sample Output:
    2
*/

/*
从第0位置,最少需要跳几次达到最后一个位置?
    如果希望最少跳跃达到终点,则需要明确何时进行跳跃是最合适的

在到达某点前若一直不跳跃,发现从该点不能跳到更远的地方溜,在这之前肯定有次必要的跳跃!
结论:在无法达到更远的地方时,在这之前应该跳到一个可以到达更远位置的位置!

设置current_max_index 为当前可达到的最远位置:
设置pre_max_max_index为在遍历各个位置的过程中,各个位置可达到的最远位置;
设置jump_为最少跳跃的次数.
利用i遍历nums,若i超过current_max_index,jump_min+1,current_max_index = pre_max_max_index
遍历过程中,若nums[i]+i(index[i])更大,则更新pre_max = nums[i] + i

*/

int Greedyalgorithm::canJump2(){
    vector<int> nums;       //to save the origin data
    vector<int> index;      //index[i] shows the ith data in nums that can reach the position in nums

    int tem;
    while (1) {
        cin >> tem;
        if (cin .get() == '\n') break;
        nums.push_back(tem);
    }
    if(nums.size() < 2){
        return  0;
    }
    int current_max_index = nums[0];
    int pre_max_max_index = nums[0];
    int jump_min = 1;

    for(int i = 1 ; i < nums.size() ; ++i){
        if( i > current_max_index){
            jump_min ++ ;
            current_max_index = pre_max_max_index;
        }
        if(pre_max_max_index < nums[i] + 1)
            pre_max_max_index = nums[i] + 1;
    }

    return  jump_min;
}


/*
leetcode 452 Minimum Number of Arrows to Burst Balloons

Question:
There are a number of spherical balloons spread in two-dimensional space.
For each balloon, provided input is the start and end coordinates of the horizontal diameter.
Since it's horizontal, y-coordinates don't matter and hence the x-coordinates of start and end of the diameter suffice. Start is always smaller than end.
There will be at most 104 balloons.An arrow can be shot up exactly vertically from different points along the x-axis.
A balloon with xstart and xend bursts by an arrow shot at x if xstart ≤ x ≤ xend.
There is no limit to the number of arrows that can be shot. An arrow once shot keeps travelling up infinitely.
The problem is to find the minimum number of arrows that must be shot to burst all balloons.

在二维空间中有许多球形的气球。对于每个气球，提供的输入是水平方向上，气球直径的开始和结束坐标。由于它是水平的，所以y坐标并不重要，因此只要知道开始和结束的x坐标就足够了。
开始坐标总是小于结束坐标。平面内最多存在104个气球。
一支弓箭可以沿着x轴从不同点完全垂直地射出。在坐标x处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足 xstart ≤ x ≤ xend，则该气球会被引爆。
可以射出的弓箭的数量没有限制。 弓箭一旦被射出之后，可以无限地前进。我们想找到使得所有气球全部被引爆，所需的弓箭的最小数量。


Example:

Input:
[[10,16], [2,8], [1,6], [7,12]]

Output:
2

Explanation:
One way is to shoot one arrow for example at x = 6
 (bursting the balloons [2,8] and [1,6]) and another arrow at x = 11 (bursting the other two balloons).

*/

/*
对于某个气球,至少需要使用1只弓箭将它击穿
在这只气球将其击穿的同时,尽可能击穿其他更多的气球(贪心)

1.对各个气球进行排序,按照气球的左端点从小到大排序
2.遍历气球数组,同时维护一个射击区间,在满足可以将当前气球射穿的情况下,尽可能击穿更多的气球,每击穿一个新的气球,更新一次射击区间
3.如果新的气球没办法击穿溜,则需要增加一个弓箭手,即维护一个新的射击区间(将该气球击穿),随后继续遍历气球数组.

*/
int Greedyalgorithm::findMinArrowShots( vector<pair<int , int>> &points){
    if (points.size() == 0){
        return 0;               //input data is empty ,return 0
    }
    std::sort(points.begin(),points.end(),cmp); //sort according to ball's left position

    int shoot_num = 1;
    int shoot_begin = points[0].first;
    int shoot_end = points[0].second;       //the shoot eara

    for(int i = 1; i < points.size() ; i ++){
        if( points[i].first <= shoot_end){
            shoot_begin = points[i].first;
            if(shoot_end > points[i].second)
                shoot_end = points[i].second;
        }
        else{
            shoot_num++;
            shoot_begin = points[i].first;
            shoot_end = points[i].second;
        }
    }
    return shoot_num;
}
bool cmp(const pair<int , int > &a , const pair<int, int> &b){
    return a.first < b.first;
}

/*
已知一条公路上,有一个起点和终点,这之间有n个加油站,已知从这n个加油站到终点的距离d与各个加油站可以加油的量l,起点位置至终点距离L与起始时刻邮箱中汽油量P;
假设使用1个单位的汽油即走一个单位的距离,邮箱没有上限,最少加几次油,可以从起点开至终点?(若不能到达终点,返回-1)

何时加油最合适?
    油用光的时候加油最合适
在哪个加油站加油最合适?
    在加油量最大多的加油站最合适

算法
    1.设置一个最大堆,用来存储经过的加油站的汽油量
    2.按照从起点至终点的方向,遍历各个加油站之间的距离
    3.每次需要走两个加油站之间的距离d,如果发现汽油不够走距离d时,从最大堆中取出一个油量添加,直到可以足够走距离d.
    4.如果把最大堆的汽油都添加仍然不够行进距离d,则无法到达终点
    5.当前油量P被减少d
    6.将当前加油站油量添加至最大堆.
*/
int Greedyalgorithm::getMinimumStop(int L , int P,                          //L为起点到终点的距离,P为起点初始的汽油量
                                    std::vector<pair<int , int>> &stop){    // pair < 加油站至终点的距离 , 加油站汽油量 >
    std::priority_queue<int> Q;                                             //存储油量的最大堆
    int result = 0;                                                         //记录加过几次油变量

    stop.push_back(std::make_pair(0,0));                                    //将终点作为一个停靠点,添加至stop数组
    std::sort(stop.begin(),stop.end(),cmp );                                //以停靠点至终点的距离 从大到小 进行排序
    for(int i = 0 ; i < stop.size() ; i ++){                                //遍历各个停靠点
        int dis = L - stop[i].first;                                        //当前要走的距离: 为当前终点距离L减去下一个停靠站点至终点距离

        while( !Q.empty() &&  P < dis  ){
            P +=Q .top();
            Q.pop();
            result ++;
        }
        if(Q.empty() && P < dis )
            return - 1;
        P = P - dis;
        L = stop[i].first;
        Q.push(stop[i].second);
    }
    return result;

}


int Greedyalgorithm::getMinimumStop(int L , int P,                          //L为起点到终点的距离,P为起点初始的汽油量
                                    std::vector<pair<int , int>> &stop){
    std::priority_queue<int>   Q;
    int result;


    stop.push_back(make_pair(0,0));

}



/*
LeetCode 122. Best Time to Buy and Sell Stock

给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1:

输入: [7,1,5,3,6,4]
输出: 7
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。

示例 2:

输入: [1,2,3,4,5]
输出: 4
解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。
     因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。

示例 3:

输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。


SampleInput:  7 1 5 3 6 4
SampleOutput: 7

SampleInput:  1 2 3 4 5
SampleOutput: 4

*/

/*
thinking :
我们希望的是在局部最小值点进行买进且在下一个局部最大值点进行卖出,即在曲线的极值点进行买进和卖出
现在的问题即转化为
    找到第一个极小值点买进,找到第二个极大值点卖出,再找下一个极小点买进,再找下一个极大值点卖出 ...

每一次买进和卖出都是局部最优情况,所有的局部最优情况即为全局最优情况..这道题应该是贪心算法

设 buy_po 为极小值点(买点), sell_po 为极大值点(卖点)
从price[1]开始逐一向前探:
    若下一个点比上一个点小,buy_po向前移一个单位
    若下一个点比上一个点大,buy_po即为此时的买点

sell_po 设为 buy_po 下一个点,也是依次向前探:
    若下一个点比上一个点大,sell_po向前移动一单位
    若下一个点比上一个点小,sell_po即为所卖点

完成一次买和卖,存入maxgain中

*/
int  bestBuyAndSellStock2(){
    vector<int> prices;
    prices.push_back(0);    //use 0 to take up position

    int tem = 0;
    while (1) {
        cin >> tem;
        prices.push_back(tem);
        if (cin.get() == '\n') break;
    }

    prices.push_back(-1);

    int sell_po = prices[1], buy_po =prices[2] ;

    static const int BEGIN = 0;
    static const int UP = 1 ;
    static const int DOWN = 2;
    int STATE = BEGIN;
    int maxgain = 0;

    for( int i = 2 ; i < prices.size() ; i ++ ){
        switch (STATE) {
        case BEGIN:
            if( prices[i - 1] < prices[i]){
                STATE = UP;
                buy_po = prices[i - 1];
            }
            else if(prices[ i - 1] > prices[i]){
                STATE = DOWN;
            }
            break;
        case UP:
            if (prices[i - 1] > prices[ i]){
                STATE = DOWN ;
                sell_po = prices[i -1];
                maxgain += sell_po - buy_po;
            }
            break;
        case DOWN:
            if (prices[i - 1] < prices [i] ){
                STATE = UP ;
                buy_po = prices [i -1 ];
            }
            break;
        default:
            break;
        }
    }

    return maxgain;

}




/*
LeetCode 860. Lemonade Change

Description：
At a lemonade stand, each lemonade costs $5.

Customers are standing in a queue to buy from you, and order one at a time (in the order specified by bills).
Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill.
You must provide the correct change to each customer, so that the net transaction is that the customer pays $5.
Note that you don’t have any change in hand at first.
Return true if and only if you can provide every customer with correct change.

Example 1:

Input: [5,5,5,10,20]
Output: true
Explanation:
From the first 3 customers, we collect three $5 bills in order.
From the fourth customer, we collect a $10 bill and give back a $5.
From the fifth customer, we give a $10 bill and a $5 bill.
Since all customers got correct change, we output true.

    1
    2
    3
    4
    5
    6
    7

Example 2:

Input: [5,5,10]
Output: true

    1
    2

Example 3:

Input: [10,10]
Output: false

    1
    2

Example 4:

Input: [5,5,10,10,20]
Output: false
Explanation:
From the first two customers in order, we collect two $5 bills.
For the next two customers in order, we collect a $10 bill and give back a $5 bill.
For the last customer, we can't give change of $15 back because we only have two $10 bills.
Since not every customer received correct change, the answer is false.

    1
    2
    3
    4
    5
    6
    7

Note:

    0 <= bills.length <= 10000
    bills[i] will be either 5, 10, or 20.

*/
