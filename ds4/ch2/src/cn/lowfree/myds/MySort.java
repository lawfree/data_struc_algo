package cn.lowfree.myds;

import org.junit.Test;

import java.util.Random;

public class MySort {

    /**
     * 比较两个元素, 若v小于w, 返回 true
     * @param v
     * @param w
     * @return 若v < w 返回true
     */
    private static boolean less(Comparable v, Comparable w)
    {return  v.compareTo(w) < 0; }

    /**
     * 交换两个元素i , j
     * @param a
     * @param i
     * @param j
     */
    private  static void  exch(Comparable[] a , int i , int j)
    {Comparable t = a[i] ; a[i] = a[j] ; a[j] = t;}

    /**
     * 打印数组 a中的所有元素
     * @param a
     */
    public static   void showSorted (Comparable[] a){
        for (int i = 0 ;i  < a.length ; i ++) {
            System.out.print( a[i] + " ");
        }
        System.out.println();
    }

    /**
     * 判断数组 a 是否已经排好序
     * @param a
     * @return true 若 a 已经是有序
     */
    public  static boolean isSorted(Comparable[] a){
        for(int i = 1 ; i < a.length ; i++){
             if (less(a[i], a[i - 1])) return  false;
        }
        return  true;
    }

    /** 选择排序 */
    public  static  void  selectSort(Comparable[] a){
        int len = a.length;

        for(int i = 0 ; i < len ; i ++){
            /*  将a[i与a[i+1,...,len-1]中最小的交换  */
            int min = i;
            for(int j = i + 1 ; j < len  ; j ++){
                if (less(j , min)) min = j;
            }
            exch(a , i , min);
        }
    }

    /** 插入排序 */
    public static void insertSort(Comparable[] a){
        int len = a.length;
        for (int i = 0 ; i < len ; i ++){
            /* 将a[i]插到a[0, ... i -1]之间 */
            for(int j = i ;  j  > 0 &&  less(a[j] ,a[j -1]) ; j --)  {
                    exch(a, j , j -1);
            }
        }
    }

    /** 希尔排序 */
    public  static  void shellSort(Comparable[] a){
        int len = a.length;
        int h = 1;
        while (h < len / 3 ) {
            h = 3 * h + 1;
        }
        while (h >= 1){
            /* 将数组变为 h 有序  */
            for(int i = 1 ; i < len ; i++ ){
                for (int j = i ; j >= h && less(a[j] , a[j- h] ); j -= h){
                    exch(a , j , j -1);
                }
            }
            h = h/3;
        }

    }

    /** 归并排序 */
    public  static  void mergeSort(Comparable[] a,int len){
        Comparable[] temp  = new Comparable[len];
//        divide(a ,0 , len - 1 , temp);
        divide_itera(a  , temp);

    }

    /* 用于分组的函数 (递归分组)*/
    private static void divide(Comparable[] a, int lo, int hi, Comparable[] temp) {
        int mid;
        if(lo <  hi){
            mid = (lo + hi) / 2;

            /* 使左边有序 */
            divide(a , lo , mid ,temp);
            /* 使右边有序 */
            divide(a , mid + 1 , hi , temp);

            merge(a , lo , mid , hi , temp);
        }
    }

    /* 迭代分组 */
    private static void divide_itera(Comparable[] a  , Comparable[] temp    ){
        //进行lgN 次两两归并排序
        for(int sz = 1 ; sz < a.length ; sz = sz + sz){
            for (int lo = 0 ; lo < a.length - sz ; lo += sz + sz)
                merge(a , lo , lo + sz -1 , Math. min(lo + sz + sz -1  , a.length - 1), temp);
        }
    }

    /* 用于合并的函数 */
    private static void merge(Comparable[] a, int lo , int mid , int hi ,Comparable[] temp ){
        int i = lo , j = mid + 1 , k = 0;

        /*当左右两边都有数时进行比较，取较小的数*/
        while(i <= mid && j <= hi){
            if  ( less(a[i] , a[j]))
                temp[k++] = a[i++];
            else
                temp[k++] = a[j++];
        }

        /*如果左边序列还有数*/
        while(i <= mid)
            temp[k++] = a[i++];

        /*如果右边序列还有数*/
        while(j <= hi)
            temp[k++] = a[j++];

        /*将temp当中该段有序元素赋值给L待排序列使之部分有序*/
        for(int x = 0; x < k ; x++)
            a[lo+ x] = temp[x];
    }


    /** 快速排序 */
    public static void quickSort(Comparable[] a , int lo , int hi){
        if( lo >= hi) return;;

        int i = lo , j = hi ;
        Comparable pivot = a[lo];

        while (i < j){
            while ((i < j) && less(pivot , a[j]))     j --;
//            if (i < j)
                a[i ++] = a[j];

            while (i < j && less (a[i] , pivot))      i ++;
//            if (i < j)
                a[j -- ] = a[i];
        }
        a[i] = pivot;

        quickSort(a , lo , i - 1);
        quickSort(a , i + 1 , hi);

    }

    /** 堆排序 */
    public static void heapSort(Comparable[] b){
        Comparable[] a = new Comparable[ b.length + 1 ];
        for(int i = 1 ; i < b.length ; i++){
            a[i] = b[i];
        }
        int N = a.length -1;

        for(int k = N /2 ; k >= 1 ; k --)
            sink(a , k , N);
        while (N > 1){
            exch(a, 1 , N --);
            sink(a , 1 , N);
        }

    }

    public static void sink(Comparable[] a, int k , int N){


        while (2 * k <= N ){
            int j = 2 * k;
            if(j < N && j < j+1) j++;
            if(k < j) break;
            exch(a , k ,j);
            k = j;
        }
    }


    @Test
    public  void test1(){
        Integer[] a = { 22,41,5,16,91,60,32,9,56,78,0,7 };

//        insertSort(a);
//        shellSort(a);
//        mergeSort(a , a.length);
//        quickSort(a , 0 , a.length -1 );
        heapSort(a);

        showSorted(a);
    }
}
