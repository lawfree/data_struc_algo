package cn.lowfree.myST;

import java.util.ArrayDeque;
import java.util.Iterator;
import java.util.Queue;


public class BST <Key extends Comparable<Key> , Value > {
    private Node root;

    private class Node{
        private Key key;
        private Value val;
        private Node left , right;
        private  int  N ;               // 以该结点为根的的子树中的结点总数

        public  Node(Key key , Value  val , int N ){
            this.key = key ;
            this.val = val;
            this.N = N ;
        }

    }
    public int size(){
        return size(root);
    }
    private int size(Node x){
        if(x == null)   return 0;
        else return  x.N;
    }

    /**
     * 二叉树查找
     * @param key
     * @return
     */
    public Object get(Key key){
        return get(root , key);
    }
    private Value get(Node x, Key key) {
        /* 在以x为根结点的子树中查找并返回key所对应的值 */
        /* 找不到则返回null */
        if(x == null) return null;
        int cmp = key.compareTo(x.key);

        if(cmp > 0) return get(x.left , key);
        else if(cmp > 0) return get(x.right, key);
        else return x.val;
    }

    public void put(Key key , Value val){
        /* 查找key,找到则更新它的值, 否则为它创建一根新的结点 */
        root = put (root , key , val);
    }

    /**
     * 二叉树更新结点值
     * @param x
     * @param key
     * @param val
     * @return
     */
    private Node put(Node x, Key key, Value val) {
        /* 如果key存在于以x为根结点的子树中则更新它的值
         * 否则以key和val为键值对的新节点插入到该子树中
         */
        if(x == null) return new Node(key , val , 1);
        int cmp = key .compareTo(x.key);
        if(cmp < 0)
            x.left = put(x.left , key , val);
        else  if (cmp > 0)
            x.right  = put(x.right , key , val);
        else x.val = val;
        x.N = size(x.left) + size(x.right) + 1;
        return  x;
    }

    /**
     * 求而叉树中的最小键
     * @return
     */
    public Key min(){
        return min(root).key;
    }
    private Node min(Node x) {
        if(x.left == null) return x;
        return min(x.left);
    }

    public  Key max(){
        return max(root).key;
    }
    private Node max(Node x){
        if(x.right == null) return  x;
        return max(x.right);
    }

    /**
     * 寻找不大于这个节点的最大节点值
     * @param
     * @param key
     * @return
     */
    public Key floor(Key key){
        Node x = floor(root , key);
        if(x == null ) return  null;
        return x.key;
    }
    private Node floor(Node x ,Key key){
        if (x == null) return  null;
        int cmp = key.compareTo(x.key);

        if(cmp == 0)    return  x;
        if(cmp < 0) return floor(x.left , key);

        Node t = floor(x.right , key);
        if(t != null) return  t;
        else return x;
    }


    /**
     * 删除tree中的键最小的结点
     */
    public void deleteMin(){
        root = deleteMin(root);
    }
    private Node deleteMin(Node x) {
        if(x.left == null)return  x.right;
        x.left = deleteMin(x.left);
        x.N = size(x.left) + size(x.right) + 1;
        return  x;
    }

    /**
     * 删除tree中键为 key 的结点
     * @param key
     */
    public void delete(Key key){
        root = delete(root , key);
    }
    private Node delete(Node x , Key key){
        if (x == null) return  null;
        int cmp = key.compareTo(x.key);
        if(cmp < 0) x.left = delete(x.left , key);
        else if(cmp > 0) x.right = delete(x.right ,  key);
        else{
            if(x.right == null) return x.left;
            if(x.left == null ) return  x.right;
            Node t = x;
            x = min(t.right);
            x.right = deleteMin(t.right);
            x.left = t.left;
        }
        x.N = size(x.left) + size(x.right) + 1;
        return  x;
    }



}
