#include "stack_queue_questions.h"

Sta_Que_Que::Sta_Que_Que(){

}

/*
poj 1363 Rails

��֪��1��n����������,��˳����ջ,ÿ��������ջ�󼴿ɳ�ջ,
Ҳ������ջ��ͣ��,�ȴ���������ֳ�ջ��ջ��,�������ڳ�ջ,����������еĳ�ջ�����Ƿ�Ϸ�

��:   3 2 5 4 1      �Ϸ�
     3 1 2 4 5      ���Ϸ�

Sample Input
    3 1 2 4 6

    5 4 3 2 1
Sample Output
     1

     0
*/

/*
ʹ��ջ�����ģ����ջ,��ջ����

�ȴ�1��ʼ������ջ,������quence�е�����ֹͣ��ջ,��ʼ��ջ
    ����order�е�Ԫ��ֵ��sim_stack����ͬʱ,����ͬʱ��ջ
    ��󿼲�sim_stack�Ƿ�Ϊ��
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
