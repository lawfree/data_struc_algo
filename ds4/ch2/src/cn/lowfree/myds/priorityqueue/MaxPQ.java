package cn.lowfree.myds.priorityqueue;

import cn.lowfree.myds.MySort;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.w3c.dom.ls.LSInput;

//@RunWith(Parameterized.class)
public class MaxPQ <Key extends  Comparable<Key> >{

    private Key[] pq ;      //基于堆的完全二叉树
    private int N = 0;      //存储于pq[1..N]中 , pq[0]没有使用



    /** 创建一个初始容量为max的优先队列 */
    public  MaxPQ(int maxN){
        pq = (Key[]) new Comparable[maxN + 1];
    }

    /** 返回队列是否为空 */
    boolean isEmpty(){
        return N == 0;
    }
    /** 返回优先队列中的元素个数 */
    int size(){
        return N ;
    }

    /** 向优先队列中插入一个元素 */
    void insert(Key v){
        pq[++N] = v;
        swim(N);
    }



    /** 返回最大元素 */
    Key Max(){
        return pq[1];
    }

    /**  删除并返回最大元素 */
    Key delMax(){
        Key max = pq[1];                //从根节点获得最大值
        exch(1 , N --);             //将其和最后一个节点交换
        pq[N + 1] = null;               //防止对象游离
        sink(1);                    //恢复堆的有序性
        return max;
    }

    private boolean less(int i , int j){
        return pq[i].compareTo(pq[j]) < 0;
    }

    private void  exch(int i , int j){
        Key tem = pq[i];pq[i] = pq[j];pq[j] = tem;
    }

    private void swim(int k) {
        while (k > 1 && less(k/2 , k)){
            exch(k/2 , k);
            k = k/2;
        }
    }

    private void sink(int k){
        while (2 * k <= N){
            int j = 2*k;
            if(j < N && less(j , j+1)) j++;
            if(!less(k , j )) break;
            exch(k , j);
            k = j;
        }
    }


    public static void main(String[] args) {


        MaxPQ<Integer> int_pq = new MaxPQ<>(10);
        int_pq.insert(5);
        int_pq.insert(20);
        int_pq.insert(8);
        int_pq.insert(3);
        int_pq.insert(0);


        while ( !int_pq.isEmpty()){
            System.out.println(int_pq.delMax());
        }
    }


}
