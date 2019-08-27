#include <iostream>

#include "dp_methods.h"

using namespace std;




int main()
{

/* climb stairs */
    int res_recur =   getWays_recur(10);

    int memo[11];
    for(int i = 0 ; i < 11 ; i++)
        memo[i] = -1;

    int res_memo = getWays_memo(10, memo);

    int res_dp = getWays_dp(10);

/* cut rod */
    int prod[] = {1,5,8,9,10,17,17,20,24,30};
    int rod_len = 10;


    int cutrod_res_recur =  cutRod_recur(prod , rod_len);
    int cutRod_res_memo= cutRod_memo(prod , rod_len );
    int cutRod_res_dp =  cutRod_dp(prod , rod_len);

/* 数字三角形(POJ1163) */
//    int i,j;
//    cin >> num_tri_n;
//    for( i = 1; i <= num_tri_n ; i++ )
//        for( j = 1 ; j <= i; j++ ){
//            cin >> num_tri[i][j];
//            num_tri_memo[i][j] = -1;
//        }
//    cout<< maxSum_memo (1,1)<<endl;


 //   cout << maxSum_dp() << endl;
    cout << maxSum_dp_2() <<endl;

//    cout<< res_recur<<endl;
//    cout<< res_memo <<endl;
//    cout<< res_dp << endl;

//    cout << cutrod_res_recur <<endl;
//    cout << cutRod_res_memo << endl;
//    cout << cutRod_res_dp  << endl;
    return 0;
}
