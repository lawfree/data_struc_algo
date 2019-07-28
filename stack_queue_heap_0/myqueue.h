#ifndef MYSTACK_H
#define MYSTACK_H

#include <stack>
using namespace std;

class MyQueue {
public:
    MyQueue();

    void push(int x);

    int pop();

    int peek();

    bool empty();
private:
    stack<int> data_stack;
};


#endif // MYSTACK_H
