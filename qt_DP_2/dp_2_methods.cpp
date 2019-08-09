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
