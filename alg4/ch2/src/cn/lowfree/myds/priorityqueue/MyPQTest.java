package cn.lowfree.myds.priorityqueue;

import org.junit.Test;
import org.omg.CORBA.COMM_FAILURE;
import org.omg.PortableInterceptor.INACTIVE;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class MyPQTest {

    public void heepSort(List a){
        a.add(0 , null);       //增加一个空置来增加下标
        int N = a.size()  -1;
        for (int k = N /2 ; k >= 1 ; k --){
            sink(a , k , N);
        }
        while ( N > 1){
            exch(a , 1 , N --);
            sink(a , 1 , N );
        }
    }

    private void exch( List list , int i , int j ){
        Comparable temp = (Comparable) list.get(i);
        list.set(i , list.get(j));
        list.set(j , temp);
    }
    private boolean   less(List<? extends  Comparable> a ,int i , int j){
        return a.get(i).compareTo(a.get(j)) < 0;
    }

    private  void sink (List<? extends  Comparable> a , int k , int N){
        while ( k * 2 < N){
            int j = 2 * k ;
            if( j < N &&  less(a ,j , j+1) ) j = j + 1;
            if( ! less(a, k , j)) break;
            exch(a , k , j);
            k = j;
        }
    }
/********************************************************************************/
    public  void heapSort(Comparable[] a){
        int N  = a .length -1 ;
        for(int k =  N /2 ; k >= 1 ; k --)
            sink(a , k , N);
        while ( N > 1){
            exch(a , 1  ,N -- );
            sink(a , 1  ,N  );
        }
    }

      void exch(Comparable[] a , int i , int j ){
        Comparable temp = a[i]; a[i] = a[j]; a[j] = temp;
    }

     boolean less(Comparable[] a , int i , int j){
        return (a[i].compareTo(a[j]) < 0) ;
    }

    private void sink(Comparable[] a , int k , int N){
        while ( 2 * k <= N){
            int j = 2 * k ;
            if(  j < N  && less(a , j, j + 1)) j ++;
            if( ! less(a ,k  , j )) break;
            exch(a , k , j);
            k = j;
        }
    }

    private void swin (Comparable[] a , int k , int N){
        while (k > 1 && less(a , k /2 , k)){
            exch(a , k/2 , k);
            k /= 2;
        }
    }


    @Test
    public void test(){
        List<Integer> list = new ArrayList<Integer>();
        list.add(85);
        list.add(27);
        list.add(10);
        list.add(54);
        list.add(33);
        list.add(0);
        list.add(75);
        list.add(60);
        list.add(8);
        for (int i  = 0; i < list .size() ; i ++ ) {
            System.out.print( list.get(i) +  " ");
        }
        System.out.println();


        heepSort(list);
        for (int i  = 1; i < list .size() ; i ++ ) {
            System.out.print( list.get(i) +  " ");
        }
    }

    @Test
    public void test2(){

        Integer[] a = {null , 33 ,5,78,23,4 , 354 ,78,114, 6};
        for (int i  = 1; i < a .length ; i ++ ) {
            System.out.print( a[i] +  " ");
        }
        System.out.println();

        heapSort(a);

        for (int i  = 1; i < a .length ; i ++ ) {
            System.out.print( a[i] +  " ");
        }
    }

}
