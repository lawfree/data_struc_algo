#include "mystack.h"

/*
 LeetCode 255 Implement Stack using Queues

 Design a stack using queue to support stack's methods.
 The queue's methods should be from the STL include
 push, peek(front), pop, size, empty, etc.
 */
MyStack::MyStack() {
}

void MyStack::push(int x) {
	queue<int> tem_queue;
	tem_queue.push(x);
	while (!data_queue.empty()) {
		tem_queue.push(data_queue.front());
		data_queue.pop();
	}
	while (!tem_queue.empty()) {
		data_queue.push(tem_queue.front());
		tem_queue.pop();
	}
}
int MyStack::pop() {
	int x = data_queue.front();
	data_queue.pop();
	return x;
}
int MyStack::top() {
	return data_queue.front();
}
bool MyStack::empty() {
	return data_queue.empty();
}


