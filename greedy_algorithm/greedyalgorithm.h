#ifndef GREEDYALGORITHM_H
#define GREEDYALGORITHM_H

#include <iostream>
#include <algorithm>
#include <string>

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

};

   bool  cmp(const pair<int , int > &a , const pair<int, int> &b);

#endif // GREEDYALGORITHM_H
