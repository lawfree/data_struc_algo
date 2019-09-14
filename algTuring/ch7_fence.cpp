//#include "someinclude.h"
#include<stdio.h>

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std ;

/*
假设有道篱笆用N个同宽的木板拼接而成.可以用一部分旧篱笆切割出长方形的木板充当木料.
给出构成篱笆的各木板的高度,编写程序计算能够切割出的最大长方形的面积.


输入:
        第一行输入一个整数N表示木板数量.下一行输入N个整数代表木板高度
输出:
        从给定的篱笆中截取的最大长方形的面积

SampleInput:
        7 1 5 9 6 7 3
SampleOutput:
        20

SampleOutput:

*/

/*
暴力法解决
    给出保存有各木板高度的数组h[],截取第l个木板到第r个木板的长方形面积可用如下公式表示.
                        (r - l + 1) x min h[i]
*/
int maxFenceArea_BruteFoce(vector<int> &vec){
    int ret = 0;
    int N = vec.size();

    for(int left = 0 ; left < N ; left++){
        int minheight = vec[left];
        for(int right = left; right < N ; right ++){
            minheight = min (minheight, vec[right]);
            ret = max(ret , (right - left + 1) * minheight) ;
        }
    }
    return ret;
}


/*
分治算法的设计
        为设计出分治算法,首先要确定以何种方式分割给定的问题.先把n个木板平均分割成两个子问题.那么我们期望的长方形会符合以下三种可能之一.
                最大面积的长方形只能在左侧的子问题中获得.
                最大面积的长方形只能在右侧的子问题中获得.
                最大面积的长方形横跨左右两侧的子问题.

        横跨左右两侧子问题的解法
                明白一个事实:该长方形必定横跨两个子问题边界的两个木板.假设从这个长方形开始分别向左右两侧一格一格扩展下去,既可向左侧一格,也可向右侧移动一格.
                那么选择"包含更高木板的右侧长方形".要找出面积最大的长方形,需要向长方形高度最大化方向寻找.全局数组h[]区间[left,right]将传递给递归函数solve().
                之后,函数将返回可在当前区间内截取的面积最大的长方形的宽度.
*/

//保存各木板高度的数组
vector<int> h;
//返回 h[left...right] 区间中可截取的面积最大长方形的宽度.
int maxFence_div(int left, int right){
    //初始部分:只有一个木板的情况
    if(left == right) return h[left];

    //分割为[left,mid]和[mid + 1, right]两个区间的子问题.
    int	mid = (left + right)  / 2;
    //分别计算分割的子问题
    int ret = max(maxFence_div(left, mid) , maxFence_div(mid + 1 , right));

    //子问题3:找出横跨两个子问题的面积最大的长方形.
    int lo = mid , hi = mid + 1;
    int height = min(h[lo] , h[hi]);
    //只考虑包含[mid, mid +１]的宽度为２的长方形．
    ret = max(ret, height * 2);

    //扩展长方形,直至覆盖所有输入值
    while (left < lo || hi < right) {
        //总是向高度更高的方向扩展
        if(hi < right && (lo == left || h[lo - 1] < h[hi + 1])) {
            hi ++;
            height = min(height , h[hi]);
        }
        else{
            lo --;
            height = min(height, h[lo]);
        }
        //扩展后的长方形宽度
        ret = max(ret , height * (hi - lo + 1));
    }
    return ret;

}


int main(int argc, char *argv[]){
    int tem = 0;
    vector<int> vec;

    while (1) {
        cin >> tem;
        h.push_back(tem);
        if (cin.get() == '\n')  break;
    }

    cout << maxFence_div(0, h.size() - 1) << endl;

    return 0;
}

