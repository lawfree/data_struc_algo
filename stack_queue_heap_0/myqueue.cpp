#include "myqueue.h"

/*
 Design a queue using stack to support queue's methods.
 The stack's methods you'll use should be from the STL include
 push, peek(front), pop, size, empty, etc.
 */
MyQueue::MyQueue() {

}
void MyQueue::push(int x) {
	stack<int> tem_stack;
	while (!data_stack.empty()) {
		tem_stack.push(data_stack.top());
		data_stack.pop();
	}
	tem_stack.push(x);
	while (!tem_stack.empty()) {
		data_stack.push(tem_stack.top());
		tem_stack.pop();
	}
}
int MyQueue::pop() {
	int x = data_stack.top();
    data_stack.pop();
	return x;
}
int MyQueue::peek() {		//return the head of queue
	return data_stack.top();
}
bool MyQueue::empty() {
	return data_stack.empty();
}
