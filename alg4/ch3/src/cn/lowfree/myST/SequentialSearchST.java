package cn.lowfree.myST;

public class SequentialSearchST<Key , Value> {
    private  Node first;
    private  class Node{    // 链表结点的定义
        Key key;
        Value val;
        Node next;
        public Node(Key key , Value  val , Node next){
            this.key = key;
            this.val = val;
            this.next = next;
        }

        public Value get (Key key){
            Node x = first;
            while (x  != null){
                if (key.equals(x.key))
                    return x.val;           // 命中
                x = x.next;
            }
            return  null;                   // 未命中
        }

        public  void put(Key key , Value val){
            Node x = first ;
            while (x != null){
                if(key.equals(x.key)){
                    x.val = val; return;
                }
                x =x.next;
            }
            first = new Node(key , val ,first);
        }

        public  int size(){
            Node x =first ;
            int size = 0;
            while (x != null){
                size ++ ;
                x = x.next;
            }
            return  size;
        }

        public  void delete(Key key){
            Node pre = first;
            while (pre .next != null){
                if(pre.next.key == key ) {
                    Node temp = pre.next;
                    pre.next = temp.next;
                    temp = null;
                }
                pre = pre .next;
            }
        }

    }
}
