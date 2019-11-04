#include<iostream>
#include<vector>
#include<string>

using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x ) : val(x) ,left(NULL) , right(NULL){}  

};

void BST_insert(TreeNode* node , TreeNode* insert_node){
    if(insert_node -> val < node -> val ){
        if(node -> left){
            BST_insert(node ->left , insert_node);
        }else
            node ->left = insert_node;
    }
    else{
        if(node ->right ){
            BST_insert(node -> right , insert_node);
        }else
        {
            node ->right = insert_node;
        }
        
    }
}

bool BST_search(TreeNode * node , int val){
    if( node ->val == val) return true;
    if(val < node ->val){
        if(node ->left)
            return BST_search(node -> left , val);
        else
            return false;
    }
    else{
        if(node -> right){
            return BST_search(node -> right , val);
        }
        else
            return false;
    }
}


/**
 * LeetCode 449 .Serialize and Desrialize BST
 */
void change_int_to_string(int val , std::string &str_val){
    string temp;
    while (val)
    {
        temp += val % 10  + '0';
        val /= 10;
    }
    for(int i = temp.length() - 1 ; i >= 0 ; i --){
        str_val += temp[i];
    }
    str_val += '#';
}
/* preorder the tree and add all nodes to string */
void BST_preorder(TreeNode *node , string &data){
    if(!node) return;
    string str_val;
    change_int_to_string(node -> val , str_val );
    data += str_val;

    BST_preorder(node -> left , data);
    BST_preorder(node -> right , data);
}

class Codec{
public:
    string serialize(TreeNode * root){
        if(!root) return NULL;
        string data;
        BST_preorder(root , data);
        return data;
    }
    TreeNode* deserialize(string data){
        if(data.empty()) return NULL;
        int val = 0;
        vector<TreeNode *> vec_tree;

        for(int i = 0 ; i < data.length() ; i ++){
           if (data[i] == '#') {
                 vec_tree.push_back(new TreeNode(val));
            }
           else {
                val = val * 10 + data[i ++];
           }
        }
        /* insert the vec_tree to tree */
        for(int i = 0 ; i < vec_tree.size() ; i ++){
            BST_insert(vec_tree[0] , vec_tree[i]);
        }
        return vec_tree[0];
    }

};





/* Test */
int main(int argc, char const *argv[])
{
    TreeNode a( 8);
    TreeNode b( 3);
    TreeNode c( 10);
    TreeNode d( 1);
    TreeNode e( 6);
    TreeNode f( 15);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;
    for(int i = 0 ; i < 20 ; i ++){
        if(BST_search(&a , i))
            cout << i << " is ok" << endl;
        else
            cout << i << "is not " << endl;
    }



    return 0;
}
