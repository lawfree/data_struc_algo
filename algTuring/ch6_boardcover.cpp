#include "someinclude.h"

/*
有一个H x W 大小的游戏板,由黑白两种单位格子组成.现要用3个单位格子的L状板块把白色格子全部覆盖,板块可以自由旋转,但不能重叠,覆盖黑色格子,超出游戏板.
编程计算出对给定的游戏板有几种覆盖方法.

输入
        第一行输入两个整数分别表示H行和W列.第二行"#"表示黑色格子,"."表示白色格子.输入的白色格子总数不超过50个.
输出
        输出覆盖白色格子的方法总数

SampleInput:
    3 7
    #.....#
    #.....#
    ##..###

SampleOutput:
    2
*/

/*
此题也属于计算组合个数的问题.因此,通过穷举搜索法计算出能够覆盖游戏板的所有可能的组合来解决此问题.
首先要处理给定白色格子不是3的倍数的情况,此时不可能存在答案,需要单独处理.
之后把白格子除以3,得到盖上白格子所需L型板的数量N.
        现在可以把整个求解过程分解为N个小的操作,每个操作视为放置1个板块.
        利用递归函数,首先在给定游戏板中放置一个板块,剩余的将使用递归调用的方式覆盖

重复计算的问题
        此问题中,摆放板块的顺序不重要,但算法会根据摆放的顺序进行重复计算,因此要强制选其特定顺序.
        简便的一个方法是在递归调用的各阶段,总是设法覆盖最左上侧的格子.这样的覆盖只能用一种方式计算出答案
        既然已经假定总是左上侧的格子开始覆盖,可判定此格子的左侧和上面的格子肯定已经背覆盖.

*/

/* 4 methods for covering to present grids */
/* 3 position(dy , dx) to make up "L" */
const int coverType[4][3][2] = {
    {{0,0}, {1,0}, {0,1} },
    {{0,0}, {0,1}, {1,1} },
    {{0,0}, {1,0}, {1,1} },
    {{0,0}, {1,0}, {1,-1} }
};
/* 把board的格子(y,x)用第type种方法进行覆盖或删除已覆盖的板块 */
/* delta = 1 表示用板块覆盖,delta = -1 则删除已覆盖的板块. */
/* 如果不能正常(超出游戏的边界,重叠,覆盖黑色格子)时,返回false. */
bool set(vector<vector<int> > &board , int y , int x , int type, int delta){
    bool ok = true;
    for(int i = 0; i < 3 ; ++i){
        const int ny = y + coverType[type][i][0];
        const int nx = x + coverType[type][i][1];
        if(ny < 0 || ny >= board.size() || nx < 0 || nx >= board.size())
            ok = false;
        else if( (board[ny][nx] += delta) > 1  )
            ok = false;
    }
    return ok;
}
/*
返回覆盖board中保存着的所有空格的方法总数
    board[i][j]=1表示已被覆盖的格子或黑色格子
    board[i][j]=0表示未被覆盖的白色格子
*/
int cover(vector<vector<int>  > board){
    /* 在剩余未被覆盖的白色格子中,寻找摆放在最左上角的格子 */
    int y = -1, x = -1;
    for(int i = 0 ; i < board.size() ; ++ i ){
        for(int j = 0 ; j < board.size() ; ++ j )
            if(board[i][j] == 0){
                y = i; x = j;
                break;
            }
        if(y != -1)
            break;
    }
    //start: has covered the white grid, then return 1
    if(y == 1) return 1;
    int ret = 0;
    for(int type = 0 ; type < 4; ++ type){
        //if can covered with "type" ,then recrusive
        if (set(board, y ,x ,type, 1));
            ret += cover(board);
        //delete the model which has been covered
        set(board , y , x ,type, -1);
    }
    return ret;
}

int main(){
    char temp;
    int H,W;
    vector<vector <int> > board;
    vector<int> v;

    cin >> H >> W;
    board.clear();
    for(int i = 0 ; i < H; i++){
        v.clear();
        for(int j = 0 ; j < W ; j ++){
            cin >> temp;
            if(temp == '#') v.push_back(1);
            else if(temp == '.')v.push_back(0);
        }
        board.push_back(v);
    }
    int ret = 0;
    ret = cover(board);
    cout << ret << endl;

    return 0;
}

