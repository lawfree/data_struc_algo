package cn.lowfree.myds;

import org.junit.Test;

import java.util.Iterator;

public class LinkStack<Item> implements Iterable<Item> {

    private  Node first;
    private  int N;
    private  class Node{
        Item item;
        Node next;
    }

    public  boolean isEmpty(){
        return  first == null;
    }
    public  int size(){
        return N;
    }
    public  void push(Item item){
        Node oldfirst =  first;
        first = new Node();
        first.item = item;
        first.next = oldfirst;
        N ++ ;
    }
    public  Item pop(){
        Item item = first.item;
        first = first .next;
        N -- ;
        return  item;
    }


    @Override
    public Iterator<Item> iterator() {
        return  new ReverseArrayIterator();
    }
    public class ReverseArrayIterator implements  Iterator<Item>{ //支持后进先出的迭代
        private  Node current = first;

        @Override
        public boolean hasNext() {
            return current != null;
        }

        @Override
        public Item next() {
            Item item = current.item;
            current = current.next;
            return  item;
        }
    }


    @Test
    public void test(){


    }
}


