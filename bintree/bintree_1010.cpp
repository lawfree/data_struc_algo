#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<queue>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode * left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};
struct ListNode
{
    int val;
    ListNode * next;
    ListNode(int x):val(x) , next(NULL){}
};

class myBinTree {

public:
    myBinTree(){}

    /*LeetCode 113. Path Sum II
     *  给定一个二叉树与整数sum, 找出所有从根节点到叶节点的路径,这些路径上的节点值累加和为sum
     */
    vector<vector<int> > pathSum(TreeNode *root , int sum){
        vector<vector<int> > result;
        vector<int> path;          //path stack
        int path_value = 0;         //save path value sum
        preorder_sum(root->left, path_value, sum , path , result );
    }
    void preorder_sum(TreeNode *node ,int &path_value , int sum , vector<int> &path , vector<vector<int> > &result){

        if(!node)   return;
        path_value += node->val;
        path.push_back(node->val);

        if(!node->left && !node->right && path_value == sum){
            result.push_back(path);
        }

        preorder_sum(node->left, path_value, sum , path , result );
        preorder_sum(node->right, path_value, sum , path , result );

        path_value -= node->val;
        path.pop_back();
    }

    /*LeetCode 236. Lowest Common Ancestor of a Binay tree
     *  已知二叉树,求二叉树中给定的两个节点的最近的公共祖先.
     *   最近公共祖先: 两节点v与w的最近公共祖先u, 满足在树上最低(离根最远),且v,w两个节点都是u的子孙.
     */
    TreeNode * lowestCommonAncestor(TreeNode* root, TreeNode* p , TreeNode* q){
        vector<TreeNode* > path ;    //temp path stack
        vector<TreeNode* > p_path;   //save p's path
        vector<TreeNode* > q_path;   //save q's path
        int finish = 0;

        preorder_path(root , p , finish, path , p_path );
        path.clear();
        finish = 0;
        preorder_path(root , q, finish , path , q_path );

        /**/
        int path_len = 0;
        if(p_path.size() - q_path.size() <= 0) path_len = p_path.size();
        else path_len = q_path.size();

        TreeNode *result;
        for(int i = 0 ; i < path_len ; i ++){
            if(p_path[i] == q_path[i])
                result = p_path[i];
        }
        return result;

    }
    /* find the path from root the the pointed node */
    void preorder_path(TreeNode* node,       //present node
                       TreeNode* search ,    //to search node
                       int &finish, vector<TreeNode *> &path, vector<TreeNode *> &result){
        if(!node || finish) return;
        path.push_back(node);
        if(node == search){
            finish =1;
            result = path;
        }

        preorder_path(node->left  , search , finish , path , result);
        preorder_path(node->right , search , finish , path , result);
        path.pop_back();

    }


    /*
      LeetCode 114. 二叉树展开为链表
     */

    /* preoder , then use a vector to save */
    void flatten_vec(TreeNode* root) {
        vector<TreeNode *> node_vec;
        preorder_addNodeToVector(root , node_vec);

        for(int i = 1 ; i < node_vec.size() ; i++){
            node_vec[i - 1] ->right= node_vec[i ];
            node_vec[i - 1] ->left = NULL;
        }

    }
    void preorder_addNodeToVector( TreeNode* node , vector<TreeNode *> &node_vec ){
        if(!node) return;
        node_vec.push_back(node);
        preorder_addNodeToVector(node->left , node_vec);
        preorder_addNodeToVector(node->right, node_vec);

    }



    void flatten_dev(TreeNode *root){
        TreeNode * last = NULL;             //last 是用来保存左子树中最后一个节点,用于与节点的右子树的第一个节点相连
        preorder_flatten(root, last);
    }
    void preorder_flatten(TreeNode *node , TreeNode* &last){        //last is out , last is a pointer and it should be changed
        if(!node)   return;
        if(!node->left && !node->right ){
            last = node;
            return;
        }
        TreeNode *left = node->left;
        TreeNode *right = node->right;      //flat过程中会修改,所以得保存一下
        TreeNode *left_last = NULL;
        TreeNode *right_last = NULL;        //分别代表左子树最后和右子树最后,等会给它传进去
        if(left){
            preorder_flatten(left, left_last);

            node -> left = NULL;
            node->right = left;             // conduct flaten
            last = left_last;               //将该节点的last保存为左子树的last
        }
        if(right){                          //若有右子树,递归将右子树倒转换单链表
            preorder_flatten(right , right_last);
            if(left_last){                  //若node找到左子树最后一个节点(有左子树)
                left_last->right = right;   // conduct flaten
            }
            last = right_last;
        }

    }

    /* 层次遍历并打印 */
    void levelTraversal(TreeNode * root){
        queue<TreeNode * > node_Q ;
        node_Q.push(root);

        while (!node_Q.empty()) {
            TreeNode *node = node_Q.front();
            cout << node->val << " ";
            node_Q.pop();
            if(node->left)
                node_Q.push(node -> left );
            if(node->right)
                node_Q.push(node -> right );

        }
    }

    /*LeetCode 199. Binary Tree Right sight view
     *  给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
     * note: pair
     */
    vector<int> rightSideView(TreeNode* root) {
        vector<int> view;       // 按层次遍历最后一个节点
        queue<pair<TreeNode * , int> > Q;

        if(root)
            Q.push(make_pair(root, 0));
        while (!Q.empty()) {
            TreeNode *node = Q.front().first;
            int deep = Q.front().second;
            Q.pop();
            if(view.size() == deep){
                view.push_back(node->val);      //此处说明是新一层的第一个节点
            }
            else{
                view[deep] = node->val;         //否则更新view数组中
            }
            if(node->left)
                Q.push(make_pair(node->left ,  deep + 1));
            if(node->right)
                Q.push(make_pair(node->right , deep + 1));
        }
        return view;
    }

private:


};

int main(int argc, char *argv[])
{
    TreeNode *a = new TreeNode(1);
    TreeNode *b = new TreeNode(2);
    TreeNode *c = new TreeNode(3);
    TreeNode *d = new TreeNode(4);
    TreeNode *e = new TreeNode(5);
    TreeNode *f = new TreeNode(6);
    TreeNode *g = new TreeNode(7);
    TreeNode *h = new TreeNode(8);
    TreeNode *i = new TreeNode(9);
    TreeNode *j = new TreeNode(10);

    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    c->right =f;
    d->left =g ; d->right = h;
    e->right = i;
    h->left = j;

    myBinTree myBinTree;

    cout << myBinTree.lowestCommonAncestor(a,d,i)->val << endl;

//    myBinTree.flatten_vec(a);
//    cout << a-> right ->val << " " << a->right->right->val << endl;
    myBinTree.levelTraversal(a);

    return 0;
}
