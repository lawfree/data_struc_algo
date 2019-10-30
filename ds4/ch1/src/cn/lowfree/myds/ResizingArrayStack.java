package cn.lowfree.myds;

import org.junit.Test;

import javax.xml.bind.annotation.adapters.XmlJavaTypeAdapters;
import java.util.Iterator;

public class ResizingArrayStack<Item> implements Iterable<Item> {
    private Item[] a = (Item[]) new Object[1];
    private int N = 0;

    public  boolean isEmpty() {return N == 0 ;}
    public  int size() { return  N;}
    public void push(Item item){
        if (N == a.length) {
            resize( 2 * a.length);
        }
        a[N++] = item;
    }

    private void resize(int max) {
        Item[] temp = (Item[]) new Object[max];
        for(int i = 0 ; i < N ; i++) {
            temp[i] = a[i];
        }
        a = temp;
    }

    public void pop(){
        Item item = a[--N];
        a[N] = null;
        if(N > 0 && N == a.length /4) {
            resize(a.length / 2);
        }
    }

    @Override
    public Iterator<Item> iterator() {
        return  new ReverseArrayIterator();
    }
    public class ReverseArrayIterator implements  Iterator<Item>{ //支持后进先出的迭代
        private  int i  = N;

        @Override
        public boolean hasNext() {
            return i > 0;
        }

        @Override
        public Item next() {
            return a[--i];
        }
    }


    @Test
    public void test(){

    }
}


