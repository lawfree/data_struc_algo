//============================================================================
// Name        : MyStack.cpp
// Author      : LowFree
// Version     :
// Copyright   : Your copyright notice
// Description : in C++, Ansi-style
//============================================================================


#include <iostream>
#include <queue>

#include "myqueue.h"
//#include "mystack.h"
#include "stack_queue_questions.h"

#define MYST 1
#define MYQU 1
#define CHE_ORDER 1
#define FLAG  MYS/*to turn to */

int main() {
	/* prepare knowledge: STL stack and queue */
	queue<int> test_queue;

	test_queue.push(1);
	test_queue.push(2);
	test_queue.push(3);
	// now the queue is  3 2 1 ,the head is 1

	cout << test_queue.front() << endl; //1
	cout << test_queue.back() << endl;  //3
	test_queue.pop();                   // pop 1, FIFO
	cout << test_queue.front() << endl; //2
	cout << test_queue.back() << endl;  //3

	/* test MyStack ,which designed with queue */
#if FLAG
    MyStack mystack;
    for (int i = 1; i <= 5; i++)
        mystack.push(i);

    cout << "mystack.pop  " << mystack.pop() << endl;
    cout << "mystack.pop  " << mystack.pop() << endl;
    cout << "mystack.top  " << mystack.top() << endl;
#endif
    /* test MyQueue ,which designed with queue */
#if FLAG
    MyQueue myqueue;
    for(int i = 1 ; i <= 5 ; i ++)
        myqueue.push(i);

    cout << "myqueue" << myqueue.pop() << endl;
    cout << "myqueue" << myqueue.pop() << endl;
    cout << "myqueue" << myqueue.peek() << endl;
#endif
    /* test check order of input  */
#if FLAG
    Sta_Que_Que sta_que_que;
    bool res_check_order = sta_que_que.check_is_vaild_order();
    cout << res_check_order << endl;
#endif

/*
prepare knowledge of heap(优先级队列 二叉堆)

二叉堆,最大(小)值先出的完全二叉树

*/
    std::priority_queue<int> big_heap;                  //默认构造最大堆
    std::priority_queue<int , std::vector<int>,
                 std::greater<int>>  small_heap;        //最小堆的构造方法
    std::priority_queue<int , std::vector<int>,
                   std::less<int>>   big_heap2;         //最大堆构造方法
    if(big_heap.empty())
        cout << "big_heap is empty! " << endl;
    vector<int> test = {6, 10, 1, 7, 99, 4, 33};
    for (int i = 0 ; i < test.size() ; i ++)
        big_heap.push(test[i]);

    cout << "big_heap.top = " << big_heap.top() << endl;//99
    big_heap.push(1000);
    cout << "big_heap.top = " << big_heap.top() << endl;//1000
    for(int i = 0 ; i < 3 ; i++)
        big_heap.pop();
    cout << "big_heap.top = " << big_heap.top() << endl;//10
    cout << "big_heap.size = " << big_heap.size() << endl;//5




    return 0;
}
