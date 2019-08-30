#include<stdio.h>

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std ;

/*
制定参数顺序

for example:
                        A 队出场顺序与历史分数表		3000	2700	2800	2200	2500	1900
                        B 队出场顺序与历史分数表		2800	2750	2995	1800	2600	2000
        假设历史分数高的队伍一定获胜,则B队按此出场顺序会获得第2,3,5,6场的胜利.此时若把第一场和第四位选手调换,则会赢得除第一场外的剩余5场胜利.
        已知对方的出场顺序时,该制定什么样的参赛顺序才能赢得更多的场次呢?
        在本题中A是对手,B是我方

*/

/*
让评分最低的选手出场
其他情况下,在能够战胜对方的选手中,让评分最低的选手出站
*/
int order(vector<int>& A , vector<int>& B){
    /*vector<int> A_order = */sort(A.begin(), A.end());
    /*vector<int> B_order = */sort(B.begin(), B.end());

    int win_count = 0;
    int game_num = 0;
    for(int i = 0 ; i < A.size(); i ++){

        for(int j = game_num ; j < B.size(); j ++){
            if(B[j] >= A[i]){
                win_count ++;
                game_num = j ;
                break;
            }

        }
    }

    return win_count;
}
int main(int argc, char *argv[])
{
    vector<int> A ,B;
    int tem = 0;
    while (1) {
        cin >> tem;
        A.push_back(tem);
        if(cin.get() == '\n')   break;
    }
    while (1) {
        cin >> tem;
        B.push_back(tem);
        if(cin.get() == '\n')   break;
    }

    cout << order(A,B) << endl;

    return 0;
}
