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
#include <iostream>

using namespace std;

int num_tri_n;
int num_tri[100][100];

int maxSum_recur( int i , int j ){

    if( i == num_tri_n)
        return num_tri[num_tri_n][j];

    int left_res = maxSum_recur(i + 1 , j);
    int right_res = maxSum_recur(i + 1 , j + 1);

    if( left_res > right_res )   right_res = left_res;

    return left_res + num_tri[i][j];

}
int main(){
    int i,j;
    cin >>num_tri_n;
    for(i = 1; i <= num_tri_n ; i++)
        for(j = 1 ; j <= i; j++)
            cin >> num_tri[i][j];

    cout<< maxSum_recur(1,1);
}
