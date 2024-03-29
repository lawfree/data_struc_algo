#include "dp_1_methods.h"

using namespace std  ;

/*
    能用动规解决的问题的特点

        1) 问题具有最优子结构性质。
            如果问题的最优解所包含的子问题的解也是最优的，我们就称该问题具有最优子结构性质。

        2) 无后效性。
            当前的若干个状态值一旦确定，则此后过程的演变就只和这若干个状态的值有关，和之前是采取哪种手段或经过哪条路径演变到当前的这若干个状态，没有关系。
*/


/*

 最长公共子序列（POJ1458)

    给出两个字符串，求出这样的一个最长的公共子序列的长度：子序列中的每个字符都能在两个原串中找到， 而且每个字符的先后顺序和原串中的先后顺序一致。

    Sample Input

        abcfbc abfcab

        programming    contest

        abcd    mnp

    Sample Output

        4

        2

        0
*/

/*
解题思路：
设输入的两个串为s1,s2,
设MaxLen(i,j)表示:：s1的左边i个字符形成的子串，与s2左边的j个字符形成的子串的最长公共子序列的长度(i,j从0 开始算），则MaxLen(i,j) 就是本题的“状态”
假定 len1 = strlen(s1),len2 = strlen(s2），那么题目就是要求   MaxLen(len1,len2)

显然：
    MaxLen(n,0)  = 0  ( n= 0…len1）
    MaxLen(0,n)  = 0  ( n=0…len2）

于是，我们可以得到如下的递推公式：
                if( s1[i - 1] == s2[ j - 1])
                    MaxLen(i,j) = MaxLen(i-1,j-1) + 1;
                else
                    MaxLen(i,j) = Max( MaxLen(i,j-1), MaxLen(i-1,j) );
*/
int dp_commonSubsequence(){
    char s1[100],s2[100];
    int max_len[100][100];

    while (cin >> s1 >> s2 ) {

        int len1 = strlen(s1);
        int len2 = strlen(s2);
        int i =0 , j = 0 ;

        /* boundary condition */
        for ( i = 0 ; i <= len1 ; i++)
            max_len[i][0] = 0;
        for ( j = 0 ; j <= len2 ; j++)
            max_len[0][j] = 0;

        for(i = 1 ; i <= len1; i++){
            for( j = 1 ; j <= len2 ; j++){
                if( s1[i - 1] == s2[ j - 1])
                    max_len[i][j] = max_len[i-1][j-1] + 1;
                else
                    max_len[i][j] = max(max_len[i][j - 1] , max_len[i - 1][j]);

            }
        }
         return max_len[len1][len2];
    }

}




/*
最长上升子序列(百练2757) (LIS)

一个数的序列ai，当a1 < a2 < ... < aS的时候，我们称这个序列是上升的。对于给定的一个序列(a1, a2, ..., aN)，我们可以得到一些上升的子序列(ai1, ai2, ..., aiK)，
这里1 <= i1 < i2 < ... < iK <= N。
比如，对于序列(1, 7, 3, 5, 9, 4, 8)， 有它的一些上升子序列，如(1, 7), (3, 4, 8)等等。这些子序列中最长的长度是4，比如子序列(1, 3, 5, 8).。
你的任务，就是对于给定的序列，求出最长上升子序列的长度。

输入数据
    输入的第一行是序列的长度N (1 <= N <= 1000)。第二行给出序列中的N个整数，这些整数的取值范围都在0到10000。

输出要求
    最长上升子序列的长度。

输入样例

    7

    1 7 3 5 9 4 8

输出样例

    4

*/

/*
解题思路

1.找子问题

    “求序列的前n个元素的最长上升子序列的长度”是个子问题，但这样分解子问题，不具有“无后效性”，因为假设F(n) = x,但可能有多个序列满足F(n) = x。
    有的序列的最后一个元素比 an+1小，则加上an+1就能形成更长上 升子序列；
    有的序列最后一个元素不比an+1小……以后的事情受如何达到状态n的影响，不符合“无后效性” ，因此我们必须换一种思路来解决此问题。

    “求以ak（k=1, 2, 3…N）为终点的最长上升子序列的长度”，一个上升子序列中最右边的那个数，称为该子序列的 “终点”。
    虽然这个子问题和原问题形式上并不完全一样，但是只要这N个子问题都解决了，那么这N个子问题的解中， 最大的那个就是整个问题的解。

2.确定状态

    子问题只和一个变量—— 数字的位置相关。因此序列中数的位置k就是“状态”，而状态 k 对应的“值”，就是以ak做为“终点”的最长上升子序列的长度。 状态一共有N个。

3.找出状态转移方程

     maxLen (k)表示以ak做为“终点”的最长上升子序列的长度

    那么：

        初始状态：maxLen (1) = 1

        maxLen (k) = max { maxLen (i)：1<=i < k 且 ai < ak且 k≠1 } + 1       若找不到这样的i,则maxLen(k) = 1

        maxLen(k)的值，就是在ak左边，“终点”数值小于ak ，且长度最大的那个上升子序列的长度再加1。因为ak左边任何“终点”小于ak的子序列，加上ak后就能形成一个更长的上升子序列。

*/


/*
有了这个思路，我们就可以很轻松地写出代码了。然而，即使到了这里，我们依然还能从两个方向解决这道题，
我们可以将它们分别称为“人人为我”递推型动归和“我为人人”递推型动归

“人人为我”递推型动归
    状态i的值Fi由若干个值 已知的状态值Fk,Fm,..Fy 推出，如求和，取最大值
*/
int dp_increaseSubsequence(){
    int a[101];         /*save original datas*/
    int max_len[101];   /*save results*/

    int n;
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        cin >> a[i];
        max_len[i] = 1;
    }

    for( int i = 2; i <= n ;i ++)
        for( int j = 1; j < i ; j++)
            if ( a[i] > a[j] )
                max_len[i] = max( max_len [i] , max_len[j] + 1);

    cout<< * max_element(max_len+1 , max_len + n +1 ) << endl;
    return 0;
}

/*
“我为人人”递推型动归
    状态i的值Fi在被更新（不一定是 最终求出）的时候，依据Fi去更 新（不一定是最终求出）和状态i 相关的其他一些状态的值 Fk,Fm,..Fy
*/
int dp_increaseSubsequence_1(){

    int a[101];         /*save original datas*/
    int max_len[101];   /*save results*/

    int n;
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        cin >> a[i];
        max_len[i] = 1;
    }

    for( int i = 2; i <= n ;i ++)
        for( int j = i + 1; j <= n ; j++)
            if ( a[j] > a[i] )
                max_len[j] = max( max_len [j] , max_len[i] + 1);

    cout<< * max_element(max_len+1 , max_len + n +1 ) << endl;
    return 0;
}

/*
动规的三种形式

1）记忆递归型
    优点：只经过有用的状态，没有浪费。递推型会查看一些 没用的状态，有浪费。
    缺点：可能会因递归层数太深导致栈溢出，函数调用带来额外时间开销。总体来说，比递推型慢。

2) “我为人人”递推型
    没有什么明显的优势，有时比较符合思考的习惯。个别特殊题目中会比“人人为我”型节省空间。

3）“人人为我”递推型
    在选取最优备选状态的值Fm,Fn,…Fy时， 有可能有好的算法或数据结构可以用来显 著降低时间复杂度。
*/


/*
2019-7-17练习

你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，能够偷窃到的最高金额。

示例 1:

    输入: [1,2,3,1]
    输出: 4
解释: 偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
         偷窃到的最高金额 = 1 + 3 = 4 。

示例 2:

    输入: [2,7,9,3,1]
    输出: 12
解释: 偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
         偷窃到的最高金额 = 2 + 9 + 1 = 12 。
*/
int dp_stealhouse(){
    int house[100];                 //house[i] saves the amount of
    int max_value[100] = {0};       //max_value[100] saves the max value

    int i = 0;


    int len = 0;
    char ch;

    while (1) {
        cin >> house[i];
        //cout << house[i] << " ";
        i++;len++;
        if(cin.get() == '\n')
            break;
    }

    /* boundary condition */
    max_value[0] = house[0];
    max_value[1] = std::max( house[1], house[0]);

    /* equation of state transition */
    for(i = 2; i < len ; i++)
        max_value[i] = std::max(max_value[i-1], max_value[i-2] + house[i]);

    cout << max_value[len-1];
    return 0;
}

/*
2019-7-18
Maximum continuous subsequence

对于形如：int arr[] = { 1, -5, 3, 8, -9, 6 };的数组，求出它的最大连续子序列和。
若数组中全部元素都是正数，则最大连续子序列和即是整个数组。
若数组中全部元素都是负数，则最大连续子序列和即是空序列，最大和就是0。

Sample Input
    6
    -2 11 -4 13 -5 -2

    10
    -10 1 2 3 4 -5 -23 3 7  -21

    6
    5 -8 3 2 5 0

    1
    10

    3
    -1 -5 -2

    3
    -1 0 -2

    0

Sample Output

    20

    10

    10

    10

    0

    0
*/

int dp_maxcontinuousSubsequence(){
    int len;
    cin >> len;

    int i ;
    int sequence[len];              //sequence save the origin data
    int maxcon_subsequence[len] ;   //maxcon_subsequence save the result
    for( i = 0 ; i < len ; i++){
        cin >> sequence[i];
        maxcon_subsequence[i] = 0;  //init the result array
    }

    for( i = 0 ; i < len ; i++)
        if (sequence[i] > 0) break;

    if(i == len - 1){
        cout << 0 << endl;
        return 0;
    }

    /* boundary condition */
    maxcon_subsequence[0] = sequence[0];

    int max = maxcon_subsequence[0];    //save the max result right now
    for(i = 1 ; i < len ; i++){
        maxcon_subsequence[i] =std::max( sequence[i] , maxcon_subsequence[i-1] + sequence[i] );
        if( maxcon_subsequence[i] > max ) max = maxcon_subsequence[i];
    }

    cout << max << endl;
}
/*
对于打家劫舍问题：
    dp的直接约束即在于不能直接相邻：选择了i，则i-1，i+1不能选择。
    思考时这样思考：对于每一个i，要么选要么不选
        若i选了，则i-1不能选，转化为i-2的情况，此时i-2也得讨论选或不选
        若i不选，则将i的问题直接转化为i-1的问题，此时i-1也得讨论选或不选

    由于有两种情况，对于每一个i，可用max函数挑选出选i或者不选i的较优值，将其放在数组中
    然后对于边界条件：	i = 0 时即为本身
                    i = 1 时比较自己和前一个大小


对于最长连续子序列问题：
    dp的直接约束在于选择了i，则需要考虑的是i-1得选或者不选的问题。
    如何找到其状态描述和状态转移方程呢？
        考虑maxSeq[i] 表示前i个的最长连续子序列的和，但是，若第i+1个本身的值就比maxSeq[i]还要大，则maxSeq[i]得变化
            这是违背无后效性的（正常情况下找到了当前maxSeq[i]，那么后面的i+k对其是不会造成影响的）
        考虑maxSeq[i] 表示以下标为i的元素作为最长子序列的结尾
            思考这样是否可行？
            最长连续子序列肯定是来自于所有这些元素的
            状态的转换就在于以i或i+1结尾


        对于一个结尾为i的最长连续子序列，那么它的前一个i-1肯定要么选要么不选
            若选则i-1，那么对于i-2 也得进行同样的讨论。此时： maxSeq[i] = sequence[i-1] + sequence[i]
            若不选择i-1，那么maxSeq[i] = sequence[i]
        类似地，比较这两种情况的较大值即为i的情况。这时候，后面的i+k的情况将不会影响i的情况（这是因为我们定义的范畴就是以i结尾的情况，i+k结尾明显是另外的范畴了）

        边界条件：maxSeq[0] = sequence[0]
*/



/*
最长递增子序列LIS (ZOJ 4028)

给定一个长度为N的数组，找出一个最长的单调自增子序列（不一定连续，但是顺序不能乱）。
例如：给定一个长度为6的数组A{5， 6， 7， 1， 2， 8}，则其最长的单调递增子序列为{5，6，7，8}，长度为4.

(叠罗汉1)
叠罗汉是一个著名的游戏，游戏中一个人要站在另一个人的肩膀上。同时我们应该让下面的人比上面的人更高一点。
已知参加游戏的每个人的身高，请编写代码计算通过选择参与游戏的人，我们多能叠多少个人。注意这里的人都是先后到的，意味着参加游戏的人的先后顺序与原序列中的顺序应该一致。

给定一个int数组men，代表依次来的每个人的身高。同时给定总人数n，请返回最多能叠的人数。保证n小于等于500。

测试样例：

    6
    1 6 2 5 3 4

返回：
    4
*/

/*
dp的约束在于，不一定连续，但是相邻两个一定是递增关系

如何找到其状态描述和转移方程呢？
    考虑long_inc_subseq[i]表示 以i为一个最长上升序列的最后一个元素 时的最长递增子序列的长度，此时该序列是动态变动的。
    对于从０～i-1中的每一个元素long_inc_subseqp[j]
        若sequence[j] < sequence[i]时
            最长子序列长度不会变化
        若sequence【j】> sequence[i]时
            此时需要找到一个以sequence[i]结尾的最长序列即可，因此需要不断地对每一个j进行比较并加和
            （之前一直想用O（n）将其化简都失败，原因在于不将0～i所有的比较完，是不能找到当前以sequence[i]的最长的子序列的）

显然边界条件为第一个元素的LIS为1;
*/
int dp_LongestIncreaseSubsequence(){
    int sequence[ 10 ];              //to save origin data
    int long_incre_subseq[ 10 ];     //save each length of the long subseq


    int len;
    int res_len;                    //length of result sequence
    cin >> len;

    for (int i = 0 ; i < len ; i++){
        cin >> sequence[i];
        long_incre_subseq[i] = 1;
    }

    long_incre_subseq[0] = 1;
    for ( int i = 1 ; i < len ; i++){

        for(int j = 0 ; j < i ; j ++) {
            if(sequence[i] > sequence[j])
                long_incre_subseq[i] = std::max ( long_incre_subseq[i] , long_incre_subseq[j] + 1 );    //
            else
                long_incre_subseq[i] = long_incre_subseq[i - 1];

        }

    }

   cout << * max_element( long_incre_subseq ,long_incre_subseq + len-1) << endl;

    return 0;
}





/*
最大连续子序列乘积

给定一个浮点数序列（可能有正数、0和负数），求出一个最大的连续子序列乘积。

Input Sample:
    1 2 3 -1 2 4

    2.5 4 -1.5 -2 -1 2

    -1 -2 -3
Output Sample:
    8

    30

    6
*/

/*
analyise

考虑到乘积子序列中有正有负也还可能有0，我们可以把问题简化成这样：
数组中找一个子序列，使得它的乘积最大；
同时找一个子序列，使得它的乘积最小（负数的情况）。
因为虽然我们只要一个最大积，但由于负数的存在，我们同时找这两个乘积做起来反而方便。也就是说，不但记录最大乘积，也要记录最小乘积。

maxmul_subsequence[i]:以下标为i的数作为结尾的序列中乘积最大的子序列
minmul_subsequence[i]:以下标为i的数作为结尾的序列中乘积最小的子序列


*/
int dp_max_mult_continuousSubsequence(){
    int sequence[10];                                      //to save origin data
    int maxmul_subsequence[10],minmul_subsequence[10] ;

    int i = 0 , len =0;

    /*save all origin datas*/
    while(1){
        cin >> sequence[i];
        len ++; i++;
        if ( cin.get() == '\n') break;
    }

    maxmul_subsequence[0] = sequence[0];
    minmul_subsequence[0] = sequence[0];

    for(i = 1 ; i < len ; i++){
        maxmul_subsequence[i] = std :: max( sequence[i]  , std::max( sequence[i] * maxmul_subsequence[i - 1] , sequence[i] * minmul_subsequence[ i - 1 ] )  );
        minmul_subsequence[i] = std :: min( sequence[i]  , std::min( sequence[i] * maxmul_subsequence[i - 1] , sequence[i] * minmul_subsequence[ i - 1 ] )  );
    }

    cout << maxmul_subsequence[len -1] << endl;
    cout << minmul_subsequence[len -1] << endl;

}
