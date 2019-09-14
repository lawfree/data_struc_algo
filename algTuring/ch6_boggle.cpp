#include "someinclude.h"


char board[5][5]  = {
    {'a', 'b', 'c', 'd', 'e'},
    {'b', 'c', 'd', 'e', 'f'},
    {'c', 'd', 'e', 'f', 'g'},
    {'d', 'e', 'f', 'g', 'h'},
    {'e', 'f', 'g', 'h', 'i'}
};
static const int dx[8] = {-1 , -1 , -1 , 1 , 1 , 1, 0 , 0};
static const int dy[8] = {-1 , 0 ,   1 , -1, 0 , 1, -1, 1};

bool inRange(int x, int y){
    if (x >= 0 && x <  5 && y >= 0 && y < 5) return true;
    return false;
}
bool hasWord(int y, int x , const string& word , int nth){
    //make sure the word's start in the 5x5 grid
    if(!inRange(x,y)) return false;

    //make sure the first character is the character at (x,y)
    if (board[x][y] != word[nth]) return false;

    //make sure the word's length is longer than 1
    if (word.size() == nth+1) return true;

    //check all 8 grid
    for(int direction = 0 ; direction < 8 ; ++ direction){
        int nextY = y + dy[direction], nextX = x + dx [direction];

        if(hasWord(nextY , nextX , word, nth + 1))
            return true;
    }

    return false;
}

int main(){


    //string word = "edcba";
    string word = "edcfd";

    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (hasWord(j, i, word, 0)) {
                cout << "Ture" << endl;
                return 0;
             }
    cout << "False" << endl;
    return 0;
}
