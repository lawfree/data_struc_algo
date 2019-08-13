#include "dp_2_methods.h"
/*
Banknotes of different denominations are known,
and how to make up a certain amount with a minimum number of banknotes,
and the minimum number of banknotes that can be used.
Returns -1 if any number of known denomination notes cannot constitute the amount.
E.g:
Banknote denomination: [1, 2, 5] Amount: 11 = 5+5+1 Requires 3 sheets
Banknote denomination: [2] Amount: 3 Unable to form, return -1
Banknote denomination: [1,2,5,7,10 Amount: 14 = 7+7 Requires 2 sheets

Sample Input:
    11
    1 2 5

    14
    1 2 5 7 10
Sample Output:
    3

    2
*/

/*
思考：
利用贪心是不是可以解决这个问题？
    钞票面值：[1,2,5,10];金额：14 最优解需要3张
    贪心思想：每次优先使用大面值的金额，如：先选1张10块的，剩下4元，再选1张2元的，剩下2元，再选1张2元的。这就可以实现
    钞票面值：[1,2,5,7,10] 金额：14 最优解需要2张(两张7块的)
这种情况下用贪心的思想来做的话，就会先选一张10块的，然后剩下4元，选了两张2块的

考虑
    less_mount[i]表示金额为i的最少使用张数
状态转移方程:
    状态i可由i-1,i-2,i-5,i-7,i-10五个状态转移所得到的(减去的这些面值,就刚好把问题规模也缩小了)
    less_mount[i] = min(less_mount[i-1],less_mount[i-2],less_mount[i-5],less_mount[i-7],less_mount[i-10]
    ) + 1
    显然我们要找的是其中面额最少的一种,由于i为一定要在所有情况中进行遍历找到最小的,所以应该是双层循环
边界条件

*/
int makeup_money(){
    int denomination = 0;
    cin >> denomination;                             //input the banknote of this time

    vector<int> coins;                              //save each coin's banknotes
    vector<int> less_mount(denomination+1,-1) ;    //save the solution from 1 to denomination

    int tem_coin = 0;
    while(1){
        cin >> tem_coin;
        coins.push_back(tem_coin);
        if(cin.get() == '\n')
            break;
    }

    /*boundray condition*/
    less_mount[0] = 0;

    /*status transfer*/
    for(int i = 1 ; i <= less_mount.size() ; i++){

        for( int j = 0 ; j < coins.size() ; j++){
            if( i - coins[j] >= 0  && less_mount[i - coins[j]] != -1)
                if( less_mount[i] == -1 || less_mount[i] > less_mount[i - coins[j]] + 1)
                    less_mount[i] = less_mount[ i - coins[j]] + 1;
        }

    }

    cout << less_mount.back() << endl;

    return 0;

}
/*
status transfer

how could we determine the equaltation of status transfer and the transfer condition?
 We have found out:
    1. less_mount[i] = min(less_mount[i-1],less_mount[i-2],less_mount[i-5],less_mount[i-7],less_mount[i-10]
    2.  i is  traversing less_nount  for getting each status (e.g. less_mout[i] = 1,2,...13,14),
        j is traversing conins for getting each coin (e.g. coins[j] =  1, 2, 5, 7 10)
    3.when should we take transfer the status?
        i - conins[j] >= 0
            means that banknote at pressent is bigger than some coins, otherwise we should skip it
        less_mount[i - coins[j]] != -1
            means that some rest banknote has a solution,otherwise skipping it
        less_mount[i] == -1 or less_mount[i] > less_mount[i - coins[j]]+1
            one case is the present banknote has not been solved yet,
            the other case is the present banknote is worse

*/

/*
Triangle (leetcode120)

given a two-dimensional array that stores a number triangle,
find the sum of all the Numbers from the top to the bottom of the number triangle and the smallest path,
each time you can go down two adjacent positions

the first line shows how many lines of the triangle
then next lines to the end is to show the elements of the triangle

Sample Input:
    3
    2
    1 2
    5 4 3

    4
    1
    2 5
    3 2 1
    4 5 2 4


Sample Output:
    8

    7
*/

/*
think about:

at first ,paths[level] saves the datas from last level,so paths[i] means that the i'th solution at some point.
So , how we find the states of transferring equaltation ?

we can work from the last level:
    if there is only one line such as the last level, the paths[] saves all the situation,
    then we can find the smallest data.And this is our boundary condition.

next we consider the second last row:
    each of the second last line' datas ,we have known that, has two paths to move(add),
    one is add with the below data ,while the anthor is with button right.

    In this case , we may find the smaller one of this two results,and them save in paths[]
    when we complete the situations of the second last row, paths[] saves the best case.
    the mallest on is what we want

nest we can see the third last row:
    everything is the same as the previous one...


how should we do this with code?

*/
int triangle_min_path(){
    int level ;
    cin >> level;

    int tri_data[level +1 ][level +1];                 //save the origin trinagle
    int paths[level];                                  //save the last level's each min paths

    /* init the origin triangle */
    for(int i = 1 ; i <= level ; i++)
        for(int j = 1 ; j <= i ; j++)
            cin >> tri_data[i][j];

    /* boundary condition */
    for (int i = 1 ; i <= level ; i++)
        paths[i] = tri_data[level][i];

    /* transfer the states */
    for(int i = level - 1 ; i >= 1 ; i --)                //do this from the second last level
        for (int j = 1 ; j <= i ; j ++)
//            paths[j] =  tri_data[i][j] + std ::min( tri_data[i+1][j], tri_data[i+1][j+1] );
            paths[j] =  tri_data[i][j] + std::min( paths[j], paths[j+1] );

    cout << paths[1];
    return 0;
}
/*
    6
    1
    1 2
    3 2 1
    1 2 3 4
    6 5 4 3 2
    2 3 5 5 7 2
    ------------
    12
*/

/*
最小路径和  LeetCode（64）：
Minimum Path Sum

Given a m x n grid containing non-negative integers,
find a path from the top left corner to the bottom right corner so that the sum of the numbers on the path is minimal.
Description: You can only move one step down or to the right at a time.

you should input two integers in the first line to show the rows and column
then you can indicate

Example:

Sample Input:
    3 3
    1 3 1
    1 5 1
    4 2 1

    3 2
    1 2
    3 5
    2 3

Sample Out:

     7

     9

Explanation:
    Because the sum of the paths 1 → 3 → 1 → 1 → 1   is the smallest.
    Because the sum of the paths 1 → 3 → 2 → 3       is the smallest.
*/

/*
Thinking:

As before, how can we define the status and determine the state transition equation?

status and state transition equation:
    we could define a grid named min_path_grid,which as big as the grid saved the originial data .
    In this grid,each position saves the minize path form the top left corner the current position.

    a little pause , we have known that each position can be reached only from it's directly above and left,
    so ,we can find that the first column's datas in min_path_grid can be directly gotten.

                1 3 4       1 4 8
                1 5 1       2 ? ?
                1 2 1       3 ? ?

    and this is also the boundary condition.
    so , we can conduct the transfer opreation form the second line and the second column.

    for each position to be operated,
        min_path_grid[i][j]  = grid[i][j] + min (min_path_grid[i][j - 1], min_path_grid[ i - 1][j]);
    among them,
        min_path_grid[i][j - 1]     means its left value,
        min_path_grid[ i - 1][j]    means its the value above it.
*/
int grid_min_path(){
    int M = 0,N = 0;
    std::cin >> M >> N;

    int grid[M + 1][N + 1];                      //save origin datas
    int min_path_grid[M + 1][N + 1];             //save the minize data from the top left corner to this corner

    /* origin datas input */
    for (int i = 1 ; i <= M ; i ++ )
        for(int j = 1 ; j <= N ;j ++ )
            cin >> grid[i][j];

    /* boundary condition */
    min_path_grid[1][1] = grid[1][1];

    for(int j = 2 ; j <= N; j ++)
        min_path_grid[1][j] = grid[1][j] + min_path_grid[1][j - 1];

    for(int i = 2; i <= M; i ++)
        min_path_grid[i][1] = grid[i][1] + min_path_grid[ i - 1][1];

    /* transfer the status */
    for(int i = 2 ; i <= M ; i ++){
        for(int j = 2 ; j <= N ; j ++){
            min_path_grid[i][j] = grid[i][j] + std::min (min_path_grid[i][j - 1], min_path_grid[ i - 1][j]);
        }
    }

    cout << min_path_grid[M][N] << endl;

}



/*
地牢游戏 LeetCode 174. Dungeon Game

The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon.
The dungeon consists of M x N rooms laid out in a 2D grid.
Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.
The knight has an initial health point represented by a positive integer.
If at any point his health point drops to 0 or below, he dies immediately.
Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon
entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).
In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.
For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

    -2 (K)  -3      3
    -5      -10     1
    10      30      -5 (P)

Note:
The knight's health has no upper bound.
Any room can contain threats or power-ups,
even the first room the knight enters and the bottom-right room where the princess is imprisoned.


you should input two integers in the first line to show the amount of rows and column
then you can indicate

Example:

Sample Input:
     3      3
    -2      -3      3
    -5      -10     1
    10      30      -5

    2       4
    -3      -1      3       2
    -2      2       -3      -5

Sample Output:
    7

    5

*/

/*
Thinking:

How can we think of this interesting question?
how can we define the status and determine the state transition equation?

we define min_heath_grid[i][j] to show that
    from this position to the terminal point , the lest health vlaues that knight should have.
    For example, when he reach the last point, we should have 6 health values or more.
    And when he reach the bottom medium point, he has 1 values of health is just ok.

how can we transfer the status?
    for each position, the value determined by the value of right or below.
    By the way ,we also determine the boundary condition.

    -2  -3  3     ?   ?   2
    -5  -10 1     ?   ?   5
    10  30 -5     1   1   6

    Mow we can determine the central position,
    in this way the health value will be decreased 10.
    when reaching right position he should remain 5,
    but 1 should be required if he turn button.
    So the lest heath is
        1 + (- dungeon[i][j]) + min( min_heath_grid[i + 1][j] , min_health_heath_grid[i][j+1] )

    -2  -3  3     ?   ?   2
    -5  -10 1     ?   12  5
    10  30 -5     1   1   6

    But if this position add health for him, we should firstly campare with the
So the equation of transfer should be:

        min_health_grid[i][j] = 1 + (- dungeon[i][j]) + min( min_heath_grid[i + 1][j] , min_health_heath_grid[i][j+1] )





*/
int dungeon_game(){
    int M = 0 , N = 0;
    cin >> M >> N;

    int dungeon[M + 1][N +1];           //to save origin datas
    int min_heath_grid[M + 1][N + 1];   //to save

    /* input the origin data */
    for (int i = 1 ; i <= M ; i++)
        for(int j = 1 ; i <= N ; j++)
            cin >> dungeon[i][j];

    /* boundary condition */
   dungeon[M + 1][N +1] > 0 ?
               min_heath_grid[M + 1][N + 1] = 1 :min_heath_grid[M + 1][N + 1] =  1 - dungeon[M + 1][N +1] ;

    for(int j = N  ; j >= 1 ; j-- )
        if (dungeon[M + 1][j] <= 0)
            min_heath_grid[M + 1][j] = min_heath_grid[M + 1][j + 1] - dungeon[M + 1][j];
        else
            min_heath_grid[M + 1][j + 1] - min_heath_grid[M + 1][j] > 0 ?
                        min_heath_grid[M + 1][j] = min_heath_grid[M + 1][j + 1] - min_heath_grid[M + 1][j] :
                        min_heath_grid[M + 1][j] =1;

    for(int i = M ; i >= 1 ; i --)
        if(dungeon[i][N + 1] <= 0)
            min_heath_grid[i][N +1] = min_heath_grid[i + 1][N + 1] - dungeon[i][N + 1];
        else
            min_heath_grid[i + 1][N + 1] - min_heath_grid[i][N + 1] > 0 ?
                        min_heath_grid[i][N + 1] = min_heath_grid[i + 1][N + 1] - min_heath_grid[i][N + 1] :
                        min_heath_grid[i][N + 1] = 1;

    /* equation of transfering of status*/
    for(int i = M ; i >= 1  ; i --)
        for(int j = N ; i >= 1 ; j --)
            if(dungeon[i][j] >= 0){
                        std::min(min_heath_grid[i + 1][j] , min_heath_grid[i][j + 1]) - dungeon[i][j] > 0 ?
                             min_heath_grid[i][j] = std::min(min_heath_grid[i + 1][j] , min_heath_grid[i][j + 1]) - dungeon[i][j]
                               : min_heath_grid[i][j] =1;
            }

    cout << min_heath_grid[1][1] << endl;

    return 0;
}



/*
leetcode 343. Integer Break

Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers.
Return the maximum product you can get.

For example, given n = 2, return 1 (2 = 1 + 1); given n = 10, return 36 (10 = 3 + 3 + 4).

Note: you may assume that n is not less than 2.

SampleInput:
    10
SampleOutput:
    36

Hint:

    There is a simple O(n) solution to this problem.
    You may check the breaking results of n ranging from 7 to 10 to discover the regularities.

题意：给一个n(n>=2),求相加等于n且乘积最大的一组整数的积。
*/


/*

设maxmul[i]代表i的最大拆分结果乘积
天然知道:
    maxmul[2] = 1 * 1 = 1
    maxmul[3] = 1 * 2 = 2


对于一个数,只用考虑将其分成两个的情况,因为再继续分的情况实际上存储了的
如当n = 10时,拆分成两个时:
    1 * 9 = 9
    2 * 8 = 16
    3 * 7 = 21
    4 * 6 = 24
    5 * 5 = 25
对于每一组的两个数,其又可以分,比如 (4 , 6)
实际我们要找的是最大的拆分: 4 * (3 * 3), 其中maxmul[6] = 3*3=9
将上面这个4一般化为j( 1 < j < n),即为:j * maxmul[n - j] ,这个式子表示拆分为两个时的最佳情况集合

n 是我们的目标数,而从4开始的每一个数都应该存入数组以便以后调用.将其一般化为 i( 3 < i <= n )
*/
int integerBreak(){
    int n = 0 ;
    cin >> n;

    vector<int> maxmul(n + 1 , 1);

    /* boundary condition */
    maxmul[2] = 1;
    maxmul[3] = 2;

    /* status transfer equation */
    for(int i = 4 ; i < n + 1 ; i ++){
        for(int j = 3; j <= i ; j ++ ){
           // maxmul[i] = std::max(  maxmul[i] ,std::max  (j * (i - j) ,j * maxmul[i -j]  ) );
           maxmul[i] =max( maxmul[i] , j * maxmul[i - j] );
        }
    }
    return maxmul[n];
}


/*
LeetCode 121. Best Time to Buy and Sell Stock

Say you have an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.
Note that you cannot sell a stock before you buy one.

Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             Not 7-1 = 6, as selling price needs to be larger than buying price.

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.


SampleInput: 7 1 5 3 6 4
SamepleOutput: 5

SampleInput: 7 6 4 3 1
SampleOutput: 0
*/


int bestBuyAndSellStock(){
    vector<int> prices;

    int tem = 0;
    while (1) {
        cin >> tem;
        prices.push_back(tem);
        if (cin.get() == '\n') break;
    }

    int minprice = prices[0];                // save the temp minize
    int maxgain = 0;                    // save the temp maxgain
    if (prices.size() == 0)
        return 0;
    for (int i = 1; i < prices.size() ; i ++){
        maxgain = max( maxgain, prices[i] - minprice );
        minprice = min ( minprice , prices[i]);
    }


    return maxgain;
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
LeetCode 123. Best Time to Buy and Sell Stock3
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most **two** transactions.
Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

Example 1:

    Input: [3,3,5,0,0,3,1,4]
    Output: 6
    Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
                 Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

Example 2:

    Input: [1,2,3,4,5]
    Output: 4
    Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
                 Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
                 engaging multiple transactions at the same time. You must sell before buying again.

Example 3:

    Input: [7,6,4,3,1]
    Output: 0
    Explanation: In this case, no transaction is done, i.e. max profit = 0.

*/


/*
错误思路（❌）: 本来想的是按之前II的low high标记每一段局部递增，然后计算局部利润，存最大的两个局部利润最后求和。但是这样用例只能通过189/200。

举个不通过的例子 [1,2,4,2,5,7,2,4,9,0]￼
按之前的局部分段利润来说是【1，2，4】=3、【2，5，7】=5、【2，4，9】=7 取5+7=12
但是正确解法是【1，2，4，2，5，7】=6、【2，4，9】=7，6+7=13
这样II的解法就行不通了。

思路2（✅)
从前往后扫描，f[i] 记录前 i 天中买卖一次的最大收益（不一定在第 i 天卖）。
从后往前扫描，计算从i th天买入能获取的最大收益，即第i天后的最大价格 - prices[i]。
两次交易的最大收益sum = 第i天买入能获取的最大收益 + f[ i -1 ]
时间复杂度O(n)
*/
int bestBuyAndSellStock3(){
    vector<int> prices;

    /* input */
    int tem = 0;
    while (1) {
        cin >> tem;
        if (cin.get() == '\n') break;
    }

    int maxgain_1 = 0 , maxgain_2 = 0;
    int minprice_1 = prices[0] , minprice_2 = prices[prices.size() - 1];
    int i = 0 ,j = prices.size() -1 ;
    while ( i != j ){
        maxgain_1 = max ( maxgain_1 ,prices[i] - minprice_1);
        minprice_1 = min( minprice_1 , prices[i] );
        i ++;

        maxgain_2 = max( maxgain_2 , prices[j] - minprice_2);
        minprice_2 = min(minprice_2 , prices[j]);
        j -- ;

    }

    return maxgain_1 + maxgain_2 ;
}


/*
Leetcode 303  Range Sum Query

Given an integer arraynums, find the sum of the elements between indicesiandj(i≤j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]
sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3

SampleInput:
    -2 0 3 -5 2 -1
    0 2
SampleOutput:
    -1
说明:
1、你可以假设数组不可变。
2、会多次调用 sumRange 方法。
*/

/*
思路：如果直接遍历求和的话，无法通过，所以用dp来记录[0,j]的和，如果求[i,j]的区间和，就用dp[j]-dp[i].
*/
class rangeSum{
public:
    vector<int> nums;

    rangeSum(){
        /* intput  */
        int low = 0, heigh = 0;
        cin >> low >> heigh;

        int tem = 0;
        while (1) {
            cin >> tem;
            if (cin .get() == '\n')
                break;
        }

        dp.resize(nums.size() + 1 , 0);
        for(int i = 1 ; i < nums.size() + 1 ; i++){
            dp[i] = dp[i - 1] + nums[i - 1];
        }

    }

    int sumRange(int low, int heigh){
        return dp[heigh + 1] - dp[low];
    }
private:
    vector<int> dp;         //dp[i] is to save the sum of nums[0] to nums[i]
};

/*
LeetCode 5: Longest Palindromic Substring

题目描述

给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为1000。
示例

输入: “babad”
输出: “bab”
注意: "aba"也是一个有效答案。

输入: “cbbd”
输出: “bb”

Sameple Input:
    badad
Sameple Output:
    bab
*/

/*
 对于字符串str，假设dp[i,j]=1表示str[i...j]是回文子串，那个必定存在dp[i+1,j-1]=1。
这样最长回文子串就能分解成一系列子问题，可以利用动态规划求解了。首先构造状态转移方程
                dp[i + 1][j - 1],       str[i] = str[j]
    dp[i][j] =
                0                       str[i] != str[j]
上面的状态转移方程表示，当str[i]=str[j]时，如果str[i+1...j-1]是回文串，则str[i...j]也是回文串；如果str[i+1...j-1]不是回文串，则str[i...j]不是回文串。

初始状态
    dp[i][i]=1
    dp[i][i+1]=1 if str[i]==str[i+1]
        上式的意义是单个字符，两个相同字符都是回文串。

*/
string findLongestPalSubstring(){
    string str ;
    cin >> str ;

    int len = str.size();
    if(str.empty()) return "";
    if(len == 1) return str;

    int longest = 1;        //save
    int start = 0;
    vector< vector< int >>  dp(len , vector<int>(len));

    /* think of all single element and two subquence and same */
    for(int i = 0 ; i < len ; i++){
        dp[i][i] = 1;
        if(i < len - 1  && str[i] == str[i + 1]){
            dp[i][i + 1] = 1;
            start = i;
            longest = 2;
        }
    }

    /* think of other condition */
    for(int l = 3 ; l <= len ; l ++){               //length of substring
        for(int i = 0 ; i + l - 1 < len ; i ++){    //enum the start of the substring
            int j = l + i - 1;  //end point
            if(str[i] == str[j] && dp[i + 1][j - 1] == 1){
                dp[i][j] = 1;
                start = i;
                longest = l;
            }
        }
    }
    return str.substr(start , longest);
}

/*
【LeetCode】647. number of Palindromic Substring

题目描述
给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。
具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被计为是不同的子串。
示例

输入: “abc”
输出: 3
解释: 三个回文子串: “a”, “b”, “c”.

输入: “aaa”
输出: 6
说明: 6个回文子串: “a”, “a”, “a”, “aa”, “aa”, “aaa”.

SampleInput:
    aaa
SampleOutput:
    6
注意:
输入的字符串长度不会超过1000。

*/

int numOfPalSubstring(){
    string str;
    cin >> str ;

    int len = str.size();
    if(str.empty()) return 0;
    if(len == 1) return 1;

    int start = 0;
    vector<vector <int>> dp(len , vector<int>(len));
    int num_substr = 0;


    for(int i = 0 ; i < len ; i ++){
        dp[i][i] = 1;
        num_substr ++ ;
        if(i < len - 1 && str[i] == str[i + 1]){
            dp[i][i + 1] = 1 ;
            num_substr ++ ;
        }
    }
    for(int l = 3 ; l <= len ; l ++){
        for(int i = 0 ; i + l - 1 < len ; i ++){
            int j = l + i - 1 ;         //end point
            if(str[i] == str[j] && dp[i + 1][j - 1] == 1){
                dp[i][j] = 1 ;
                num_substr ++;
            }
        }
    }
    return num_substr;

}

/*
LeetCode 413. Arithmetic Slices

A sequence of number is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
For example, these are arithmetic sequence:

1   3   5   7
7   7   7   7
3  -1  -5  -9

A zero-indexed array A consisting of N numbers is given. A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.

A slice (P, Q) of array A is called arithmetic if the sequence:
A[P], A[p + 1], …, A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.

The function should return the number of arithmetic slices in the array A.

SampleInput:
     1 2 3 4
SampleOutput:
    3
        for 3 arithmetic slices in 1 2 3 4:
        1 2 3, 2 3 4, 1 2 3 4
*/
int numOfAritSlices(){
    vector<int> nums;
    int count = 0;

    int tem;
    while (1) {
        cin >> tem;
        nums.push_back(tem);
        if(cin .get() == '\n') break;
    }

    vector<int> dp( nums.size() , 0 );

    dp[0] = dp[1] = 0;
    for(int i = 2 ; i < nums.size() ; i ++ ){
        if( nums[i] - nums[i -1] == nums[i - 1] - nums[i -2])
            dp[i] = dp[i - 1] + 1;
        count += dp[i];
    }

    return count;
}


/*

给定两个字符串s1, s2，找到使两个字符串相等所需删除字符的ASCII值的最小和。

示例 1:

输入: s1 = "sea", s2 = "eat"
输出: 231
解释: 在 "sea" 中删除 "s" 并将 "s" 的值(115)加入总和。
在 "eat" 中删除 "t" 并将 116 加入总和。
结束时，两个字符串相等，115 + 116 = 231 就是符合条件的最小和。

示例 2:

输入: s1 = "delete", s2 = "leet"
输出: 403
解释: 在 "delete" 中删除 "dee" 字符串变成 "let"，
将 100[d]+101[e]+101[e] 加入总和。在 "leet" 中删除 "e" 将 101[e] 加入总和。
结束时，两个字符串都等于 "let"，结果即为 100+101+101+101 = 403 。
如果改为将两个字符串转换为 "lee" 或 "eet"，我们会得到 433 或 417 的结果，比答案更大。

注意:

    0 < s1.length, s2.length <= 1000。
    所有字符串中的字符ASCII值在[97, 122]之间。


*/
