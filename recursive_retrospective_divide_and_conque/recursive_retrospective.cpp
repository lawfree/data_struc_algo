#include "recursive_retrospective.h"

Recursive_retrospective::Recursive_retrospective(){

}


/*
LeetCode 78,Subsets

��֪һ����(�������ظ�Ԫ��),��������������ɵ������Ӽ�
����в��������ظ����Ӽ�

����: ����: 1 2 3
���Ϊ: [[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]]
*/

/*
�������Ӽ���,���ɸ����Ӽ�, [[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]]
����ѡ[1],�Ƿ�ѡ[2],�Ƿ�ѡ[3]������

���ֻʹ��ѭ��,����������?
ʹ��ѭ������ֱ��ģ���Ƿ�ѡĳһԪ�صĹ���

���ֻ������[1],[1,2],[1,2,3]�����Ӽ�,�����?
*/
void Recursive_retrospective::subSets(){
    vector<int> nums;

    int tem;
    while(1){
        cin >> tem;
        nums.push_back(tem);
        if( cin.get() == '\n')  break;
    }

    vector<int> item;           //item, ���ɸ����Ӽ�������
    vector<vector<int>> result; //result,���ս������


    result.push_back(item);     //push empty set in
    generate(0 , nums, item , result);


    for(int i = 0 ; i < result.size() ; i ++){
        for(int j = 0 ; j < result[i].size() ; j ++){
            cout << result[i][j] << " " ;
        }
        cout << endl;
    }
    return ;
}

void generate(int i, vector<int>& nums, vector<int> &item, vector<vector<int>> &result){



    if(i >= nums.size())
        return;
    item.push_back(nums[i]);
    result.push_back((item));
    generate(i + 1,nums,item,result);

    item.pop_back();
    generate(i + 1, nums, item, result);
}


/*

*/
