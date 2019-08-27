#include "mystack_min.h"

/*
LeetCode 155 MinStack

design a stack to support opreations below, and these opreations should
be in O(1):
push(x)     push x into the stack
pop()       pop the top elsement of the stack
top()       return the top of the stack
getMin()    return the minize element of the stack

*/

/*
考虑一个变量能否记录最小值?
    1.个变量无法完成记录栈中 所有状态 下的最小值
    2.栈的 每个状态 ,都需要有一个变量记录最小直

将 -2 0 -3压入栈中
    data_stack: -2  0   -3
    min_stack:  -2  2   -3
出栈
    data_stack: -2  0
    min_stack:  -2  2


*/
MinStack::MinStack(){

}
void MinStack::push(int x){
    data_stack.push(x);
    if(min_stack.empty())
        min_stack.push(x);
    else{
        if(x > min_stack.top())
            x = min_stack.top();
        min_stack.push(x);
    }

}

void MinStack::pop(){
    data_stack.pop();
    min_stack.pop();
}
int MinStack::top(){
    return data_stack.top();
}
int MinStack::getMin(){
    return min_stack.top();
}
