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
};

void generate(int i, vector<int>& nums, vector<int> &item, vector<vector<int>> &result);
void generateII(int i, vector<int>& nums, vector<vector<int>> &result, vector<int> &item, set<vector<int> > &res_set);
int generateBracket(string item, int n, vector<string> &result );

#endif // RECURSIVE_RETROSPECTIVE_H
