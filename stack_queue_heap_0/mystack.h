#ifndef MYSTACK_H
#define MYSTACK_H

#include <queue>
using namespace std;

class MyStack {
public:
	MyStack();

	void push(int x);

	int pop();

	int top();

	bool empty();
private:
	queue<int> data_queue;   // datas' order in data_queue is as
};
// same as in stack

#endif // MYSTACK_H
