#include<stdio.h>

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std ;
/*
活动选择问题
        能否用暴力解决法
                此题有多种答案,互不重叠的会议集合都是此题的答案,所要求的最优解就是这些集合的最大的一个.此题的暴力解决法就是,生成所有子集,并在其中找出不重叠的最大集合.
                不过,集合的大小是n的时候,子集的个数是2^n.所以n=30时,就不可能在限定时间内完成运算.
        构思贪心法
                考虑从开会时间最短的会议开始逐个检索,并找出不与前面的会议发生冲突的会议.这种方法可将使用会议室的时间变为最大.不过,算法只选择最短的一个,而不是选择两个唱的.
                由此可见使用贪心的算法原理上可行,但不能保证一定能够得到正确答案.

                解决此问题的贪心法应该从最早结束的会议开始选择.选择最早结束的会议后,删除与这个会议冲突的会议,然后再从中选择最早结束的会议.反复进行此操作就能得到最终答案.
                算法具有如下结构:
                        1.在会议室目录中S中选取最早结束的会议Smin
                        2.在会议目录S中删除与Smin发生冲突的会议
                        3.重复上述两步骤直到S为空
                使用此方法是否能够选出最多的会议?

        正确性证明:贪心选择性质
                贪心法的正确性证明在很多情况下会表现一种特定模式,这种模式通过证明两个属性体现贪心法求出的最优解的正确性.
                第一个要证明的属性是,就像动态规划一样,在不考虑整体答案的前提下,只使用贪心法进行选择,也能够求出最优解.
                这种属性被称为贪心选择性.
                若一个算法中这种性质成立,那么在各个阶段进行贪心选择将是求出最优解的途径之一.这也就说明,贪心选择不会产生任何损失.如果上面提出的算法贪心选择性成立,
                那么意味着下面的条件也将会成立:
                        必定存在一个最优解包含最早结束的会议(Smin).

                        证明:	假设S的最优解中有一个不包含Smin的答案.这个解是一个相互不重叠的会议记录,在这个目录中删除第一个要举行的会议后,添加Smin生成一个新目录.
                                                因Smin是S中最先结束的会议(或之一),被删除的会议不可能在Smin之前结束.因此,第二个会议也不可能与Smin发生冲突.这说明,新生成的目录也是一个最优解,而且也可以
                                                证明出包含Smin的最优解是存在的.这个证明说明,不存在"选择最先结束的会议而求不出最优解"的情况.

        最优子结构
                即使已经证明了贪心选择能够求出最优解,但整个证明还未结束.还需要证明,算法始终做出最佳选择,并能够求出最终的最优解.比如,做出第一个选择后,剩余部分需使用非最优的方法解决.
                为了证明贪心法的正确性,需要证明的第二个属性就是最优子结构.

        实现方法
                首先把会议按照结束时间的升序排列.这时可以先选择第一个会议,然后并不需要删除重叠会议,而是检索已排序好的数组,选出与第一个会议不发重叠的会议即可.
                会议已按照升序排列,所以找不到不重叠的会议后,不用再检索其他会议,直接选用即可.
*/
bool cmp(pair<int , int> a, pair<int , int> b){
    return a.first < b.first;
}

int maxShedule(vector< pair<int , int> > &order ){

    vector< pair<int , int>> sort_order = order;
    sort(sort_order.begin() , sort_order.end() , cmp);

    int n = sort_order.size();

    /* earliest: next meeting earliest time */
    /* selected: the number of meetings that selected */
    int earliest = 0, selected = 0;

    for(int i = 0 ; i < sort_order.size() ; i ++){
        int meetingBegin = sort_order[i].second, meetingEnd = order[i].first;

        if(earliest <= meetingBegin){
            //refreash the earliest to the last meeting's end
            earliest = meetingEnd;
            selected ++;
        }
    }
    return selected;
}


int main(int argc, char *argv[])
{
    vector<pair <int , int>>vec ;
    vec.push_back({1,3});
    vec.push_back({2.5});
    vec.push_back({4,8});

    return 0;
}
