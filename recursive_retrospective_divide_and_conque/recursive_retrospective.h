#ifndef RECURSIVE_RETROSPECTIVE_H
#define RECURSIVE_RETROSPECTIVE_H


#include <iostream>
#include <vector>
#include <string>
#include <queue>


using namespace std;

class Recursive_retrospective
{
public:
    Recursive_retrospective();

    void subSets();
};

void generate(int i, vector<int>& nums, vector<int> &item, vector<vector<int>> &result);

#endif // RECURSIVE_RETROSPECTIVE_H
