#include "heap_questions.h"


Heap_Ques::Heap_Ques(){

}

/*
LeetCode 215 Kth Largest Element in an Array

��֪һ��δ���������,����������е�k�������
��: array = [3,2,1,5,6,4] , k = 2 ,return 5

Sample Input
    3 2 1 5 6 4
    2
Sample Output
    5
*/

/*
˼·:
ά��һ�� k ��С����С��,����Ԫ�ظ���С�� k ʱ.��Ԫ��ֱ�ӽ����;
����,���Ѷ�С����Ԫ��ʱ,�����Ѷ�,����Ԫ�ؼ����

����:
���ڶ�����С��,�Ѷ��Ƕ�����С��Ԫ��,��Ԫ�ض��ᱣ֤�ȶѶ�Ԫ��С(������Ԫ���滻�Ѷ�),
��˶��е� k ��Ԫ���Ѿ���ɨ���Ԫ�������� k ��;�Ѷ���Ϊ�� k �����.
���鳤��Ϊ N,��� k �����,ʱ�临�Ӷ�Ϊ Nlogk

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

���һ�����ݽṹ,�����ݽṹ��̬ά��һ������,��֧�����²���:
    1.���Ԫ��: void addNumber(int),������num��������ݽṹ��
    2.�������ݵ���λ��:double findMedian(), ����ά�����ݵ���λ��

��λ������:
    �����ݸ���Ϊ����,��λ���Ǹ�������������м����    [1,2,3] -> 2
    �����ݸ���Ϊż��,��λ���Ǹ�������������м����������ƽ��ֵ    [1,2,3,4] -> 2.5

*/

/*
��ֱ�۵ķ���

�洢�ṹʹ������,ÿ�����Ԫ�ػ������λ��ʱ����������,�ټ�����
ʱ�临�Ӷ�:
    ���Ԫ��ʱ����,    addNum O(n)     findMedian���Ӷ�O(1)
    ��ѯ��λ��ʱ����,   addNum O(n)    findMedian���Ӷ�O(nlog)

    ������Ԫ�ػ��ѯ��λ��ʱ�������,�� n �β���,���帴�Ӷ�ΪO(n^2)


˼·:
    ��̬ά��һ�����Ѻ�һ����С��,���Ѵ洢һ������,��С�Ѵ洢һ������,ά�����ѵĶѶ�����С�ѵĶѶ�С
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
