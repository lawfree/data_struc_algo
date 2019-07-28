#include "stack_queue_questions.h"

Sta_Que_Que::Sta_Que_Que(){

}

/*
poj 1363 Rails

已知从1到n的数字序列,按顺序入栈,每个数字入栈后即可出栈,
也可以在栈中停留,等待后面的数字出栈入栈后,该数字在出栈,求该数字序列的出栈序列是否合法

如:   3 2 5 4 1      合法
     3 1 2 4 5      不合法

Sample Input
    3 1 2 4 6

    5 4 3 2 1
Sample Output
     1

     0
*/

/*
使用栈与队列模拟入栈,出栈过程

先从1开始依次入栈,当遇到quence中的数后停止入栈,开始出栈
    即当order中的元素值和sim_stack中相同时,两个同时出栈
    最后考察sim_stack是否为空
*/
bool Sta_Que_Que::check_is_vaild_order(){
    std::queue<int> order;              //the quence to check if is vaild order
    std::stack<int> simu_stack;         //to simulate the process of pop and push
    int n = 0 ;

    /* input the data */
    int tem;
    while (1) {
        cin >> tem;
        order.push(tem);
        if (cin.get() == '\n') break;
    }
    n = order.size();

    for(int i = 1 ; i <= n ; i++){
        simu_stack.push(i);
        while (!simu_stack.empty() && order.front() == simu_stack.top() ) {
            simu_stack.pop();
            order.pop();
        }
    }
    if (!simu_stack.empty())
        return false;
    return true;


}
