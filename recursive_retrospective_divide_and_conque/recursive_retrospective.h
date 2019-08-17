#ifndef RECURSIVE_RETROSPECTIVE_H
#define RECURSIVE_RETROSPECTIVE_H


#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>


using namespace std;

class Recursive_retrospective
{
public:
    Recursive_retrospective();

    void subSets();
    void subSetsII();
    int numOfBrackets();
    int numOfCombBrackets();
    vector<vector <string>> solveNQueens(int n);
};

void generate(int i, vector<int>& nums, vector<int> &item, vector<vector<int>> &result);
void generateII(int i, vector<int>& nums, vector<vector<int>> &result, vector<int> &item, set<vector<int> > &res_set);
int generateBracket(string item, int n, vector<string> &result );
int generateCombBracket(string item , int left , int right , vector<string> &result);
void put_down_the_queen(int x , int y , vector< vector<int> > &mark);
void generateNQueens(int k , int n , vector<string> &location , vector<vector<string> > &result , vector<vector <int> >  &mark);


#endif // RECURSIVE_RETROSPECTIVE_H
