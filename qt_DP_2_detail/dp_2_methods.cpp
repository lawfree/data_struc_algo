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

you should input two integers in the first line to show the length and width
then you can indicate

Example:

Sample Input:
    3 3
    1 3 1
    1 5 1
    4 2 1

    2 3
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


int grid_min_path(){
    int M = 0,N = 0;
    cin >> M >> N >> endl;


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

*/
int dungeon_game(){

}
