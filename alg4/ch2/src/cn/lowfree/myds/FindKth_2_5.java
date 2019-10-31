package cn.lowfree.myds;

public class FindKth_2_5 {
    /**
     * 找到一组数中的第k小元素
     * @param a
     * @param k
     * @return
     */
    public static Comparable selectK(Comparable[] a , int k){
        int  lo = 0 , hi = a .length - 1 ; Comparable pivot = a[lo];
        while ( hi > lo){
            int i = lo , j = hi ;


            while (i < j){
                while ((i < j) && pivot.compareTo(a[j]) < 0)    j --;
                a[i ++] = a[j];

                while (i < j && a[i].compareTo(pivot) < 0)      i ++;
                a[j -- ] = a[i];
            }
            a[i] = pivot ;
            /* get i and pivot */
            if(i == k) return a[k];
            else if(i > k) hi = i - 1;
            else if(i < k) lo = i + 1;
        }
        return a[k];
    }

    public static void main(String[] args) {
        Integer[] a = {33 ,5,78,23,4,354,78,114, 6};
        for (int i  = 0; i < a .length ; i ++ ) {
            System.out.print( a[i] +  " ");
        }
        System.out.println();

        System.out.println( selectK(a, a.length /2) );
    }
}
