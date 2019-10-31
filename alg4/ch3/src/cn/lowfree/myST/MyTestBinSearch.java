package cn.lowfree.myST;

import org.junit.Test;

public class MyTestBinSearch {

    /** 递归式二分查找 */
    public int binSearch_Recur(Comparable[] a , int lo , int hi , Comparable target){

        if( lo > hi ) return lo;
        int mid = (lo + hi) /2;
        int flag = a[mid] .compareTo( target);
        if( flag > 0)
            return  binSearch_Recur(a , lo , mid - 1, target);
        else if(flag < 0)
            return binSearch_Recur(a, mid + 1, hi, target);
        else
            return mid;
    }

    /** 迭代二分查找 */
    public int binSearch_Itrea(Comparable[] a ,Comparable target){
        int lo = 0 , hi = a.length - 1;
        while (lo <= hi){
            int mid = (lo + hi) /2;
            int flag = a[mid] .compareTo( target);

            if(flag > 0)
                hi = mid -1;
            else if(flag < 0)
                lo = mid + 1;
            else return mid;
        }
        return lo;
    }

    @Test
    public  void test(){
        Integer[] a = {0 ,5 ,7, 9, 16 ,32 ,22 };
        for (int i  = 0; i < a .length ; i ++ ) {
            System.out.print( a[i] +  " ");
        }
        System.out.println();

        int res = binSearch_Recur(a,0,a.length - 1 , 56);
        System.out.println(res);
        System.out.println();

        System.out.println(binSearch_Itrea(a,9));
    }
}
