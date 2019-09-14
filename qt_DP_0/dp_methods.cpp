#include"dp_methods.h"


/*
概念

动态规划(dynamic programming)是运筹学的一个分支，是求解决策过程(decision process)最优化的数学方法。
动态规划算法通常基于一个递推公式及一个或多个初始状态。 当前子问题的解将由上一次子问题的解推出。


基本思想

要解决一个给定的问题，我们需要解决其不同部分（即解决子问题），再合并子问题的解以得出原问题的解。
通常许多子问题非常相似，为此动态规划法试图只解决每个子问题一次，从而减少计算量。

一旦某个给定子问题的解已经算出，则将其记忆化存储，以便下次需要同一个子问题解之时直接查表。
这种做法在重复子问题的数目关于输入的规模呈指数增长时特别有用。

动态规划有三个核心元素：
    1.最优子结构
    2.边界
    3.状态转移方程
*/


/*
有一座高度是10级台阶的楼梯，从下往上走，每跨一步只能向上1级或者2级台阶。求出一共有多少种走法。


比如，每次走1级台阶，一共走10步，这是其中一种走法。
再比如，每次走2级台阶，一共走5步，这是另一种走法。

但是这样一个个算太麻烦了，我们可以只去思考最后一步怎么走
    如果最后一步上1级，则倒数第二步时已经走到第9级
    如果最后一步上2级，则倒数第二步走到的是第8级


    这样走到第十个楼梯的走法 = 走到第八个楼梯的走法 + 走到第九个楼梯的走法
    我们用f(n)来表示 走到第n个楼梯的走法，所以就有了f(10) = f(9) + f(8)
    然后f(9) = f(8) + f(7), f(8) = f(7) + f(6)......

这样我们就得出来一个递归式：
    f(n) = f(n-1) + f(n-2);
还有两个初始状态：
    f(1) = 1;
    f(2) = 2;

*/

/*  方法一：递归求解

    这种方法的时间复杂度为O(2^n)
*/
int getWays_recur(int n){

    if (n < 1)  return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    return getWays_recur(n-1)+getWays_recur(n-2);

}

/*
可以看到递归调用的模式一颗二叉树，数的节点个数就是我们递归方程需要计算的次数，
数的高度为N，节点个数近似于2^n
所以时间复杂度近似于O(2^n)

但是这种方法能不能优化呢？
我们会发现有些值被重复计算

我们可不可以把这些重复计算的值记录下来呢？
这样的优化就有了第二种方法
*/


/* 方法二：备忘录算法 */
int getWays_memo(int n , int* memo){

    if(n < 1) return 0;
    if(n == 1) return 1;
    if(n == 2) return 2;


    if(memo[n] != -1)
        return memo[n] ;

    int value  = getWays_memo( n-1 , memo)+ getWays_memo(n-2, memo);
    memo[n] = value;

    return value;

}

/*
因为map里最终会存放n-2个键值对，所以空间复杂度为O(n),时间复杂度也为O(n)

继续想一想这就是最优的解决方案了吗？

我们回到一开始的思路，我们是假定前面的楼梯已经走完，只考虑最后一步，所以才得出来f(n) = f(n-1) + f(n-2)的递归式，这是一个置顶向下求解的式子
一般来说，按照正常的思路应该是一步一步往上走，应该是自底向上去求解才比较符合正常人的思维，我们来看看行不行的通

    台阶数 1 2 3 4 5 6 7 8 9
    走法数 1 2

    这是一开始走的一个和两个楼梯的走法数,即之前说的初始状态

    台阶数 1 2 3 4 5 6 7 8 9
    走法数 1 2 3

    这是进行了一次迭代得出了3个楼梯的走法，f(3)只依赖于f(1) 和 f(2)

    台阶数 1 2 3 4 5 6 7 8 9
    走法数 1 2 3 5

    这里又进行了一次迭代得出了4个楼梯的走法，f(4)只依赖于f(2) 和 f(3)

我们发现每次迭代只需要前两次迭代的数据，不用像备忘录一样去保存所有子状态的数据
*/

/* 方法三：动态规划求解 */
int getWays_dp(int n){

    if (n < 1) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    /* a保存倒数第二个子状态数据，b保存倒数第一个子状态数据， temp 保存当前状态的数据*/
    int a = 1 , b = 2;
    int temp = a + b;

    for(int i = 3 ; i <= n ;i++){
        temp = a + b;
        a = b;
        b = temp;
    }
    return temp;
}

/*
这是我们可以再看看当前的时间复杂度和空间复杂度
当前时间复杂度仍为O(n)，但空间复杂度降为O(1)
这就是理想的结果
*/

/**********************************************************************************************************************************/



/*
例题：钢条切割

Serling公司购买长钢条，将其切割为短钢条出售。切割工序本身没有成本支出。公司管理层希望知道最佳的切割方案。
假定我们知道Serling公司出售一段长为i英寸的钢条的价格为pi(i=1,2,…，单位为美元)。钢条的长度均为整英寸。图给出了一个价格表的样例。

长度i	1	2	3	4	5	6	7	8	9	10
价格pi   1	5	8	9	10	17	17	24	24	30

钢条切割问题是这样的：
给定一段长度为n英寸的钢条和一个价格表pi(i=1,2,…n)，求切割钢条方案，使得销售收益rn最大。
注意，如果长度为n英寸的钢条的价格pn足够大，最优解可能就是完全不需要切割。

*/

/*
问题分析

长度为n英寸的钢条共有2^(n-1)种不同的切割方案，因为在距离钢条左端i(i=1,2,…n)英寸处，总是可以选择切割或不切割。

如果一个最优解将钢条切割为k段（对某个1 <= k <= n)，那么最优切割方案 n = i1 + i2 + i3 + ... + ik ，将钢条切割为长度分别为i1,i2...ik的小段得到的最大收益为
        rn = pi1 + pi2 + ... + pik


对于 n >= 1，rn = max(pn, r1 + rn-1,r2 + rn-2,...,rn-1 + r1)。
其中，pn对应不切割，对于每个i=1,2,…,n-1，首先将钢条切割为长度为i和n-i的两段，接着求解这两段的最优切割收益ri和rn-i(每种方案的最优收益为两段的最优收益之和)。
当完成首次切割后，我们将两段钢条看成两个独立的钢条切割问题实例。通过组合两个相关子问题的最优解，并在所有可能的两段切割方案中选取组合收益最大者，构成原问题的最优解。


钢条切割问题还存在一种相似的但更为简单的递归求解方法：将钢条从左边切割下长度为i的一段，只对右边剩下的长度为n-i的一段继续进行切割，对左边的一段则不再进行切割。
即问题分解的方式为：将长度为n的钢条分解为左边开始一段，以及剩余部分继续分解的结果。
这样得到的公式为：rn = max(pi + rn-i)   [1 <= i <= n]。这样原问题的最优解只包含一个相关子问题（右端剩余部分）的解，而不是两个。

*/

/* 自顶向下递归实现 */
int cutRod_recur(int *p , int n){

    if( n == 0) return 0;

    int q = -1 ;

    for( int  i = 0 ; i <n ;i++){
        int temp = p[i] + cutRod_recur(p , n - i - 1);

        if(q < temp)
            q = temp;
    }
    return q;

}
/*
递归很好理解，如果不懂可以看上面的讲解，递归的思路其实和回溯法是一样的，遍历所有解空间但这里和上面斐波拉契数列的不同之处在于，
在每一层上都进行了一次最优解的选择，q=Math.max(q, p[i-1]+cut(p, n-i));这个段语句就是最优解选择，这里上一层的最优解与下一层的最优解相关。
*/


/* 带备忘的自顶向下法
该方法依然按照自然的递归形式编写过程，但是过程中会保存每个子问题的解。当需要一个子问题的解时，过程首先检查是否已经保存过此解。
如果是，则直接返回保存的值，从而节省了计算时间；否则按照通常的方式计算这个子问题。
*/
int cutRod_memo(int *p , int n){
    int r[n+1];

    for (int i = 0 ; i <= n ; i++)   r[i] = -1;

    return cutRod_memo_aux(p, n, r);
}
int cutRod_memo_aux(int *p, int n, int *r){

    int q = -1 ;

    if( n == 0) q = 0;
    if( r[n] >= 0)  return r[n];    //检查所需的值是否存在

    for( int i = 1 ; i <= n; i++){
        int tmp = p[i - 1 ] + cutRod_memo_aux(p , n-i , r);
        if (q < tmp)
            q = tmp;
    }
    r[n] = q;

    return q;
}
/*
有了上面求斐波拉契数列的基础，理解备忘录方法也就不难了。
备忘录方法无非是在递归的时候记录下已经调用过的子函数的值。
这道钢条切割问题的经典之处在于自底向上的动态规划问题的处理，理解了这个也就理解了动态规划的精髓。
*/


/* 自底向上的动态规划

这种方法需要恰当定义子问题“规模的概念”，使得任何子问题的求解都只依赖“更小的”子问题的求解。
因而我们可以将子问题按规模排序，按由小到大的顺序进行求解。当求解某个子问题时，它所依赖的更小的子问题都已经求解完毕，结果已经保存。
每个问题最需要求解一次，当我们求解它时，它的所有前提子问题都已求解完成

*/
int cutRod_dp(int *p , int n){

    int r[n + 1];
    r[0] = 0;

    for(int j = 0 ; j < n ;j++){

        int q = -1;
        // (1)
        for(int i = 0 ; i <= j ;i++){
            int tmp = p[i] + r [ j - i  ];
            q = q > tmp ? q : tmp;
        }
        r[j + 1 ] = q;
    }
    return r[n];

}
/*

自底向上的动态规划问题中最重要的是理解注释 (1) 处的循环，这里外面的循环是求r[1],r[2] ...，
里面的循环是求出r[1],r[2]……的最优解，也就是说r[i]中保存的是钢条长度为i时划分的最优解，
这里面涉及到了最优子结构问题，也就是一个问题取最优解的时候，它的子问题也一定要取得最优解。下面是长度为4的钢条划分的结构图。

*/


/*********************************************************************************************************************/

/*
例题:

    数字三角形(POJ1163)

    在上面的数字三角形中寻找一条从顶部到底边的路径，使得路径上所经过的数字之和最大。
    路径上的每一步都只能往左下或 右下走。只需要求出这个最大和即可，不必给出具体路径。
    三角形的行数大于1小于等于100，数字为 0 - 99


输入格式：

    5      //表示三角形的行数    接下来输入三角形

    7

    3   8

    8   1   0

    2   7   4   4

    4   5   2   6   5

要求输出最大和
*/

/*解题思路：

首先，肯定得用二维数组来存放数字三角形

    然后我们用 num_tri( r, j) 来表示第r行第 j 个数字(r,j从1开始算)

    我们用maxSum(r, j)表示从 num_tri(r,j)到底边的各条路径中，最佳路径的数字之和。

    因此，此题的最终问题就变成了求 maxSum(1,1)

    当我们看到这个题目的时候，首先想到的就是可以用简单的递归来解题：

    D(r, j)出发，下一步只能走 num_tri(r+1,j)或者 num_tri(r+1, j+1)。故对于N行的三角形，我们可以写出如下的递归式：

    if ( r == N)
        maxSum(r,j) = num_tri(r,j)
    else
        maxSum( r, j) = Max{ MaxSum(r＋1,j), maxSum(r+1,j+1) } + num_tri(r,j)

*/

int num_tri[101][101] = {0};
int num_tri_n = 0 ;

int maxSum_recur( int i , int j ){

    if( i == num_tri_n)
        return num_tri[num_tri_n][j];

    int left_res = maxSum_recur(i + 1 , j);
    int right_res = maxSum_recur(i + 1 , j + 1);

    if( left_res < right_res )
        return right_res + num_tri[i][j];
    else
        return left_res + num_tri[i][j];
}

/*
就拿第三行数字1来说，当我们计算从第2行的数字3开始的MaxSum时会计算出从1开始的MaxSum，
当我们计算从第二行的数字8开始的MaxSum的时候又会计算一次从1开始的MaxSum，也就是说有重复计算。这样就浪费了大量的时间。
也就是说如果采用递规的方法，深度遍历每条路径，存在大量重复计算。则时间复杂度为 2的n次方,对于 n = 100 行，肯定超时。

接下来，我们就要考虑如何进行改进，我们自然而然就可以想到如果每算出一个MaxSum(r,j)就保存起来，
下次用到其值的时候直接取用，则可免去重复计算。那么可以用n方的时间复杂度完成计算。因为三角形的数字总数是 n(n+1)/2

*/
int num_tri_memo[101][101];

int maxSum_memo(int i , int j){

    if (num_tri_memo[ i ][ j ] != -1)
        return num_tri_memo[i][j];

    if ( i == num_tri_n)
        num_tri_memo[i][j] = num_tri[i][j];

    else{
        int left_res = maxSum_memo(i+1 , j);
        int right_res = maxSum_memo(i + 1 , j + 1);

        if( left_res < right_res )
            num_tri_memo[i][j]  =  right_res +  num_tri[i][j];
        else
            num_tri_memo[i][j]  =  left_res  +  num_tri[i][j];
    }
    return num_tri_memo[i][j];
}

/*

虽然在短时间内就AC了。但是，我们并不能满足于这样的代码，因为递归总是需要使用大量堆栈上的空间，很容易造成栈溢出，
我们现在就要考虑如何把递归转换为递推
让我们一步一步来完成这个过程。

我们从底层开始一层一层逐渐向上,找出每次相加所能得到的最大值


    7

    3   8

    8   1   0

    2   7   4   4

    4   5   2   6   5




    30

    23  21

    20  13   10

    7   12   10   10

    4   5    2    6    5


理解之后我们就可以写出如下的递推型动态规划程序：
*/
int num_tri_dp[101][101];

int maxSum_dp( ){

    int i , j ,n;
    cin >> n;

    for(i = 1 ; i <= n; i++ )
        for( j = 1 ; j <= i; j++)
            cin >> num_tri[i][j];

    for(int i =1 ; i <= n ;i++)
        num_tri_dp[n][i] = num_tri[n][i];

    for(int i =n - 1; i >= 1 ; i--)
        for(int j = 1 ; j <= i ; j++)
            num_tri_dp[i][j] = num_tri[i][j] + max(num_tri_dp[i+1][j] , num_tri_dp[i+1][j+1]);

    return  num_tri_dp[1][1] ;
}

/*
进一步考虑，我们甚至可以连maxSum数组都可以不要，直接用D的第n行直接替代maxSum即可。但是这里需要强调的是：虽然节省空间，但是时间复杂度还是不变的。

    依照上面的方式，我们可以写出如下代码：
*/
int maxSum_dp_2(){
    int* num_tri_dp_2;

    int i , j , n;
    cin >> n;

    for(i = 1 ; i <= n ; i++)
        for (j = 1 ; j <= i ; j++)
            cin >> num_tri[i][j];

    num_tri_dp_2 = num_tri[n];      /*  num_tri_dp_2 point to the n th line of num_tri[n] */

    for(int i = n - 1 ; i >= 1 ; i --)
            for(int  j = 1 ; j <= i ; j++)
                    num_tri_dp_2[j] = num_tri[i][j] + max(num_tri_dp_2[j], num_tri_dp_2[ j+1 ]);
    return num_tri_dp_2[1] ;
}



/*
总结：

递归到动规的一般转化方法

    递归函数有n个参数，就定义一个n维的数组，数组的下标是递归函数参数的取值范围，数组元素的值是递归函数的返回值，
    这样就可以从边界值开始， 逐步填充数组，相当于计算递归函数值的逆过程。

动规解题的一般思路
    1. 将原问题分解为子问题
        把原问题分解为若干个子问题，子问题和原问题形式相同或类似，只不过规模变小了。子问题都解决，原问题即解决(数字三角形例）。

        子问题的解一旦求出就会被保存，所以每个子问题只需求 解一次。
   2.确定状态
        在用动态规划解题时，我们往往将和子问题相关的各个变量的一组取值，称之为一个“状 态”。
        一个“状态”对应于一个或多个子问题， 所谓某个“状态”下的“值”，就是这个“状 态”所对应的子问题的解。

        所有“状态”的集合，构成问题的“状态空间”。“状态空间”的大小，与用动态规划解决问题的时间复杂度直接相关。
        在数字三角形的例子里，一共有N×(N+1)/2个数字，所以这个问题的状态空间里一共就有N×(N+1)/2个状态。

        整个问题的时间复杂度是状态数目乘以计算每个状态所需时间。在数字三角形里每个“状态”只需要经过一次，且在每个状态上作计算所花的时间都是和N无关的常数。

    3.确定一些初始状态（边界状态）的值
        以“数字三角形”为例，初始状态就是底边数字，值就是底边数字值。

    4. 确定状态转移方程

        定义出什么是“状态”，以及在该“状态”下的“值”后，就要找出不同的状态之间如何迁移――即如何从一个或多个“值”已知的 “状态”，求出另一个“状态”的“值”(递推型)。
        状态的迁移可以用递推公式表示，此递推公式也可被称作“状态转移方程”。

        数字三角形的状态转移方程:
                                num_tri[i][j]                                                       i = n
            num_tri_dp[i][j] =
                                num_tri[i][j] + max(num_tri_dp[i+1][j] , num_tri_dp[i+1][j+1])      i < n


    能用动规解决的问题的特点

        1) 问题具有最优子结构性质。
            如果问题的最优解所包含的子问题的解也是最优的，我们就称该问题具有最优子结构性质。

        2) 无后效性。
            当前的若干个状态值一旦确定，则此后过程的演变就只和这若干个状态的值有关，和之前是采取哪种手段或经过哪条路径演变到当前的这若干个状态，没有关系。

*/
