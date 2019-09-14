#include "someinclude.h"

void quickSort(vector<int> &vec, int start, int end){
    int i, j , pivot;
    if (start < end){
        i = start;
        j = end;
        pivot = vec[start];
    }else
        return;

    while ( i < j ) {
        while (i < j && vec[j] >= pivot)
            j --;

        if(i < j)
           vec[ i++ ] = vec[j];

        while (i < j && vec[i] <= pivot)
            i ++;

        if(i < j)
            vec[j -- ] = vec[i];
    }
    vec[i] = pivot;

    quickSort(vec, start, i - 1);
    quickSort(vec, i + 1, end);

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

    quickSort(vec, 0 , vec.size() - 1);

    for(int i = 0  ; i < vec.size() ; i ++)
        cout << vec[i] << " ";
    cout << endl;
    return 0;
}
