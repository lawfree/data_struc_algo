#ifndef MYSTACK_MIN_H
#define MYSTACK_MIN_H
#include<iostream>
#include<stack>

class MinStack
{
public:
    MinStack();

    void push(int);

    void pop();

    int top();

    int getMin();
private:
    std::stack<int> data_stack;     //data stack : save datas
    std::stack<int> min_stack;      //min value stac: save the minize value of each status

};


#endif // MYSTACK_MIN_H
