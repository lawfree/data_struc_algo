#include "heap_questions.h"


Heap_Ques::Heap_Ques(){

}

/*
LeetCode 215 Kth Largest Element in an Array

已知一个未排序的数组,求这个数组中第k大的数字
如: array = [3,2,1,5,6,4] , k = 2 ,return 5

Sample Input
    3 2 1 5 6 4
    2
Sample Output
    5
*/

/*
思路:
维护一个 k 大小的最小堆,堆中元素个数小于 k 时.新元素直接进入堆;
否则,当堆顶小于新元素时,弹出堆顶,将新元素加入堆

解释:
由于堆是最小堆,堆顶是堆中最小的元素,新元素都会保证比堆顶元素小(否则新元素替换堆顶),
因此堆中的 k 个元素已经是扫描的元素里最大的 k 个;堆顶即为第 k 大的数.
数组长度为 N,求第 k 大的数,时间复杂度为 Nlogk

3   2   2 >1    2<5 -> 3       3<6 -> 5    5>4
   3   3       3      5       5      6    6
*/
Heap_Ques::findKthLargestInHeap(){
    int k = 0;
    std::vector<int> nums;

    /* input the origin datas to nums */
    int tem;
    while (1) {
        cin >> tem;
        nums.push_back(tem);
        if(cin.get() == '\n')
            break;
    }
    cin >> k;

    std::priority_queue<int , std::vector<int> , std::greater<int>> min_heap;
    for(int i = 0 ; i < nums.size() ; i ++){
        if (min_heap.size() < k)
            min_heap.push(nums[i]);
        else if( min_heap.top() < nums[i] ){
            min_heap.pop();
            min_heap.push(nums[i]);
        }
    }
    return min_heap.top();
}

/*
LeetCode 295 ,Find Midian from Data Stream

设计一个数据结构,该数据结构动态维护一组数据,且支持如下操作:
    1.添加元素: void addNumber(int),将整型num添加至数据结构中
    2.返回数据的中位数:double findMedian(), 返回维护数据的中位数

中位数定义:
    若数据个数为奇数,中位数是该数组数排序后中间的数    [1,2,3] -> 2
    若数据个数为偶数,中位数是该数组数排序后中间的两个数的平均值    [1,2,3,4] -> 2.5

*/

/*
最直观的方法

存储结构使用数组,每次添加元素或查找中位数时对数组排序,再计算结果
时间复杂度:
    添加元素时排序,    addNum O(n)     findMedian复杂度O(1)
    查询中位数时排序,   addNum O(n)    findMedian复杂度O(nlog)

    如果添加元素或查询中位数时随机操作,共 n 次操作,整体复杂度为O(n^2)


思路:
    动态维护一个最大堆和一个最小堆,最大堆存储一半数据,最小堆存储一半数据,维持最大堆的堆顶比最小堆的堆顶小
*/
MedianFinder::MedianFinder(){

}
void MedianFinder::addNumber(int num){
    if(big_queue.empty()){
        big_queue.push(num);
        return;
    }
    if(big_queue.size() == small_queue.size()){
        if(num < big_queue.top())
            big_queue.push(num);
        else
            small_queue.push(num);
    }
    else if(big_queue.size() > small_queue.size()){
        if(num > big_queue.top())
            small_queue.push(num);
        else{
            small_queue.push(big_queue.top());
            big_queue.pop();
            big_queue.push(num);
        }
    }
    else if(big_queue.size() < small_queue.size()){
        if(num < small_queue.top())
            big_queue.push(num);
        else{
            big_queue.push(small_queue.top());
            small_queue.pop();
            small_queue.push(num);
        }

    }
}
double MedianFinder::finMedian(){
    if(big_queue.size() == small_queue.size())
        return (big_queue.top() + small_queue.size()) / 2;
    else if(big_queue.size() > small_queue.size())
        return big_queue.top();
    return small_queue();
}
