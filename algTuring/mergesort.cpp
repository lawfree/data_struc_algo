#include "someinclude.h"

void mergeTwoSubvec(vector<int> &vec1, vector<int> &vec2 , vector<int> &vec){
    int i = 0, j = 0;
    while (i < vec1.size() && j < vec2.size()) {
        if(vec1[i] < vec2[j])
            vec.push_back(vec1[i ++ ]);
        else
            vec.push_back(vec2[j ++ ]);
    }
    for(; i < vec1.size(); i ++)
        vec.push_back(vec1[i]);
    for(; j < vec2.size(); j ++)
        vec.push_back(vec2[j ++]);

}
void mergeSort(vector<int> &vec){
    if(vec.size() < 2)
        return;

    int mid = vec.size() / 2;
    vector<int> vec1;
    vector<int> vec2;
    for(int i = 0 ; i < mid ; i ++)
        vec1.push_back(vec[i]);
    for(int j = mid ; j < vec.size() ; j ++)
        vec2.push_back(vec[j]);

    mergeSort(vec1);
    mergeSort(vec2);

    vec.clear();;
    mergeTwoSubvec(vec1,vec2,vec);
}
int main(int argc, char *argv[]){
    int tem = 0;
    vector<int> vec;

    while (1) {
        cin >> tem;
        vec.push_back(tem);
        if (cin.get() == '\n')
            break;
    }

    mergeSort(vec);

    for(int i = 0  ; i < vec.size() ; i ++)
        cout << vec[i] << " ";
    cout << endl;
    return 0;
}

