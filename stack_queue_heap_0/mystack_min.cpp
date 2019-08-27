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
����һ�������ܷ��¼��Сֵ?
    1.�������޷���ɼ�¼ջ�� ����״̬ �µ���Сֵ
    2.ջ�� ÿ��״̬ ,����Ҫ��һ��������¼��Сֱ

�� -2 0 -3ѹ��ջ��
    data_stack: -2  0   -3
    min_stack:  -2  2   -3
��ջ
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
