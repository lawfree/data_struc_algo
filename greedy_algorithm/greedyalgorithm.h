#ifndef GREEDYALGORITHM_H
#define GREEDYALGORITHM_H

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <map>

using namespace std;


class Greedyalgorithm
{
public:
    Greedyalgorithm();

    int assignCandies();

    int wiggleSubsequence();

    string removeKdigits();

    bool canJump();

    int canJump2();

    int findMinArrowShots(vector<pair<int, int>>& points);

    int getMinimumStop(int L , int P, std::vector<pair<int , int>> &stop) ;

    int bestBuyAndSellStock2();

    bool lemonadeChange();

    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) ;

    int monotoneIncreasingDigits();

};

bool  cmp(const pair<int , int > &a , const pair<int, int> &b);
bool cmpheight(pair<int,int> a,pair<int,int> b);

#endif // GREEDYALGORITHM_H
