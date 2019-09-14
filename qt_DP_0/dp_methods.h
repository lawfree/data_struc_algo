#ifndef DP_METHODS_H
#define DP_METHODS_H

#include <time.h>
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;


/* climb stairs */
int getWays_recur(int n);

int getWays_memo(int n, int *memo);

int getWays_dp(int n);

/* cut rod */

int cutRod_recur(int* p , int n);

int cutRod_memo(int *p , int n);
int cutRod_memo_aux(int *p , int n ,int *r);

int cutRod_dp(int *p , int n);


/* 数字三角形(POJ1163) */
extern int num_tri[101][101];
extern int num_tri_n;
int maxSum_recur(int i , int j );

extern int num_tri_memo[101][101];
int maxSum_memo(int i , int j);

extern int num_tri_dp[101][101];
int maxSum_dp( );

int maxSum_dp_2();


#endif // DP_METHODS_H
