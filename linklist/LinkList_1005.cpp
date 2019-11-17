#include<iostream>

#include<stdio.h>
#include<malloc.h>

#include<vector>
#include<set>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
    ListNode(): val(int(NULL)), next(NULL){}
};


struct RandomListNode       //带有随机指针的链表节点
{
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x): label(x) , next(NULL), random(NULL) {}
};

class MyLinklist
{
public:
    MyLinklist() {}

    /* print all nodes of a list */
    void printNodes(ListNode *head){
        while (head != NULL) {
            cout << head->val << "->" ;
            head = head ->next;
        }
        cout << endl;
    }



    /*LeetCode 206. Reverse Linked List
        reverse a linklist without other zone
    */
    ListNode* reverseList(ListNode *head){

        ListNode *new_head = head;
        ListNode *p = new_head ->next, *q = p ->next;
        if(p == NULL ) return p;
        if(q == NULL){
            p -> next = new_head;
            new_head ->next = NULL;
            return p;
        }
        new_head ->next = NULL;
        while (p != NULL ) {
            p ->next = new_head; new_head = p;
            p = q ;
            if(p != NULL) q = q -> next;        //  caution!  while q = NULL , q = q -> next will be wrong
        }
        return new_head;

    }

    /* LeetCode 92. Reverse LinkList II
        as known head pointer, reverse the list from position m to n
    */
    ListNode * reverseListBetween(ListNode *head , int m , int n){
        ListNode *pre_m , *pm, *pn, *n_next;
        ListNode *p = head, *q;

        /* find four key nodes */
        int count = 0;
        while ( p !=NULL && count < n) {
            /* without pre_m */
            if(m ==1){
                pre_m = NULL;
                pm = head;
            }
            if(m >= 2 &&count == m -2){
                pre_m = p;
                pm = pre_m ->next;
            }

            if(count == n - 1 ){
                pn = p;
                n_next = pn -> next;
            }
            count ++ ;
            p = p ->next;
        }

        /* conduct the reverse */
        p = pm -> next; q = p -> next;
        ListNode *new_head = pm;
        while (p != n_next) {
            p ->next = new_head;
            new_head = p;
            p = q ;
            if(q != NULL)q = p ->next;
        }

        /* link front and end */
        if(pre_m != NULL){
            pre_m ->next = pn;
            pm ->next = n_next;
            return pre_m;
        }else{
            pm ->next = n_next;
            return pn;
        }
    }



    /*  LeetCode 160. Intersection of Two Linklists
        已知链表A的头结点指针headA,链表B的头结点指针headB,两个链表相交,求两个链表交点对应的结点.

        如果两个链表没有交点,则返回NULL
        在求交点过程中,不可以破会链表结构或者修改链表数据域
        可以保证传入链表A与B没有任何环
        实现算法尽可能使时间复杂度O(n),空间O(1)
    */
    /* method 1 :
        use set
    */
    ListNode *getIntersectionNodeSet(ListNode* headA , ListNode* headB){
        set<ListNode *> node_set;
        while (headA) {
            node_set.insert(headA);
            headA = headA -> next;
        }
        while(headB){
            if(node_set.find(headB) != node_set.end()){
                return headB;
            }
            headB = headB ->next;
        }
    }
    /*
     * method 2:
     *  1. count lengths of headA and headB, and count the short
     *  2. move the pointer to the same position as shorter's
     *  3. two pointers move together, until point to the same one
     */
    ListNode * getIntersectionNodeOn1(ListNode *headA, ListNode *headB){
        /* 1. */
        int countA = 0, countB = 0 , lenAB = 0 , lenBA = 0;

        ListNode *p = headA , *q = headB;       //notice:  don't use headA and headB to count the length
        while (p) {
            countA ++ ;
            p = p ->next;
        }
        while (q) {
            countB ++ ;
            q = q-> next;
        }
        if(countA > countB)   lenAB = countA - countB;
        else
            lenBA = countB - countA;

        /* 2. */
        while  (lenAB > 0) {
            headA = headA ->next;
            lenAB --;
        }

         while (lenBA > 0) {
             headB = headB -> next;
             lenBA --;
        }
        while (headA && headB ) {
            if(headA == headB) break;
            headA = headA -> next;
            headB = headB -> next;
        }
        return headA;
    }

    /*LeetCode 142. Linked List Cycle II
     *  已知链表中可能存在环,若有环返回环起始点,否则返回NULL
     */

    /* method1:
     *       use set
     */
    ListNode *detectCycleSet(ListNode *head){
        set<ListNode *> node_set ;
        while (head !=NULL) {
            if(node_set.find(head) != node_set.end())
                return head;
            node_set.insert(head);
            head = head->next;
        }
        return NULL;
    }

    /* method:
     *    ***  快慢指针 ***
     *
     */
    ListNode *detectCycleFastSlowPointer(ListNode *head){
        ListNode *fast = head, *slow = head;
        ListNode *meet = NULL;
        fast = head ->next ->next;
        slow = slow ->next;

        while (fast != NULL && slow != NULL && fast != slow) {
            fast = fast ->next ->next;
            slow = slow ->next;
        }

        if(fast == NULL) return NULL;
        else {
            meet = slow;
            ListNode *step = head;
            while (step != slow ) {
                step = step -> next;
                slow = slow -> next;
            }
            return step;
        }

    }

    /* LeetCode 86. Partition List
     *
     *  已知链表头指针head与数值x,将所有小于x的节点放在大于或等于x的节点前,且保持这些节点的原来相对位置
     */
    ListNode * partition(ListNode *head , int x){
        ListNode *less_head = new ListNode(); ListNode *q1 = less_head;
        ListNode *more_head = new ListNode(); ListNode *q2 = more_head;
        ListNode *pre = head, *p = head ->next;

        while (p) {
            if(pre -> val < x){
                q1 -> next = pre;
                q1 = q1 -> next;
            }else{
                q2 -> next = pre;
                q2 = q2->next ;
            }
            pre = p ; p = pre -> next;
        }
        q1 -> next = more_head -> next;
        return less_head -> next;
    }

    /* LeetCdde 138. Copy List with Random Pointer
     *
     *      已知一个复杂链表,节点中有一个指向本链表任意某个节点的随机指针,求这个链表的深度拷贝
     *
     *  solve:
     *      此题最难的地方在于将原链表中的random指针的关系在新链表中复现出来
     *           原链表节点地址 -> 节点位置(第几个节点)
     *           节点位置(第几个节点) -> 新链表节点地址
     *
     */
    RandomListNode *copyRandomList(RandomListNode *head){
        map<RandomListNode * , int> node_map;   //address -> node position
        vector<RandomListNode *> node_vec;
        RandomListNode *ptr = head;             //use vector to
        int i = 0;

        while (ptr) {           //将新链表节点push入node_vec,生成了新链表节点位置到地址的map
            node_vec .push_back(new RandomListNode(ptr -> label));
            node_map[ptr] = i;      // 记录原始链表地址至节点位置的node_map
            ptr = ptr->next;
            i ++;
        }
        node_vec.push_back(0);
        ptr = head;
        i = 0;
        while (ptr) {               //再次便利原始列表, 连接新链表的next指针,random指针
            node_vec[i] ->next = node_vec[i + 1] ;      //连接新链表的next指针
            if(ptr -> random){      //当random飞空
                int id = node_map[ptr ->random];        //according to node_map
                node_vec[i] -> random = node_vec[id];   //原链表random指针指向的位置即id
            }
            ptr = ptr -> next;
            i ++;
        }
        return node_vec;
    }


    /* LeetCode 21. Merge Two Sorted List
     *
     *     已知两个已排序链表头结点指针l1与l2,将这两个链表合并,合并后仍为有序的,返回合并后的头结点.
     */
    ListNode *mergeTwoLinkList(ListNode *l1 , ListNode *l2){
        ListNode tem_head(0);
        ListNode *pre = &tem_head;

        while ( l1 && l2) {
            if(l1->val < l2->val){
                pre ->next = l1;
                l1 = l1 ->next;
            }else{
                pre ->next = l2;
                l2 = l2 ->next;
            }
            pre = pre ->next;
        }
        if(l1){
            pre ->next = l1;
        }
        if(l2){
            pre ->next = l2;
        }
        return tem_head.next;

    }


    /* LeetCode 23. Merge k Sorted Lists
     *
     *      已知k个已排序链表头结点指针将k个链表合并,合并后仍为有序的,返回合并后的头结点.
     */

    /*
       方法1: 暴力合并
            k个链表按顺序合并k-1次
            设有k个链表,平均每个链表有n个节点,时间复杂度:
                (n + n) + (2n + n) + ((k - 1)n + n) = (1+2+...+k-1)n + (k-1)n = (1+2+...+k)n -n=(k^2 + k-1)/2 * n =O(k^2 *n)

        方法2: 排序后相连
            将k*n个节点放到vector中,再将vector排序,再将节点顺序相连.
            设k个链表平均每一个链表n个节点,时间复杂度:
                kN*logkN + kN =O(kN * logkN)

        方法3: 分治后相连
                对k个链表进行分治,两两进行合并
                设有k个链表,平均每个链表有n个节点,时间复杂度:
                        第一轮,进行k/2次,每次处理2个数字;第二轮,进行k/4次,每次处理4n个数字; ...;
                        最后一次,进行k/(2^logk)次,每次处理2^log*N个值.
                2N*k/2 + 4N*k/4 + 8N * k/8 + ... + 2^logk*N *k(2^logk)= Nk + Nk _... Nk = O(kNlogk)
     */
    ListNode * nergeKListNodes_sort(vector<ListNode *> &lists){
        vector<ListNode *> node_vec;
        for(int i = 0 ; i < lists.size(); i++){
            ListNode *head =lists[i];
            while (head) {
                node_vec.push_back(head);
                head = head ->next;
            }
        }
        if(node_vec.size() == 0){
            return NULL;
        }

        sort(node_vec.begin() , node_vec.end() , cmp);
        for(int i = 1 ; i < node_vec.size() ; i++){     //link new linklist
            node_vec[ i - 1] ->next = node_vec[i];
        }
        node_vec[node_vec.size() -1] ->next = NULL;
        return node_vec[0];
    }

    ListNode * mergeKListNodes_dev(vector<ListNode *> &lists){
        if(lists.size() == 0){
            return NULL;
        }
        if (lists.size() == 1){
            return lists[0];
        }
        if(lists.size() == 2 ){     //if there is two lists , directly call
            return mergeTwoLinkList(lists[0] , lists[1]);
        }
        int mid = lists.size() / 2;

        vector<ListNode *> sub1_lists;
        vector<ListNode *> sub2_lists;
        for(int i = 0 ; i < mid ; i++){
            sub1_lists.push_back(lists[i]);
        }
        for(int i = mid ; i < lists.size() ; i++){
            sub2_lists.push_back(lists[i]);
        }

        ListNode *l1 = mergeKListNodes_dev(sub1_lists);
        ListNode *l2 = mergeKListNodes_dev(sub2_lists);

        return mergeTwoLinkList(l1 , l2);

    }

};

bool cmp(const ListNode *a , const ListNode *b){
    return a->val < b->val;
}

int main(int argc, char *argv[])
{
    ListNode *h1 = new ListNode(1);
    ListNode *n2 = new ListNode(2);
    ListNode *n3 = new ListNode(3);
    ListNode *n4 = new ListNode(4);
    ListNode *n5 = new ListNode(5);
    ListNode *n6= new ListNode(6);
    ListNode *n7= new ListNode(7);
    h1 ->next  = n2; n2 -> next = n3; n3 -> next = n4; n4 ->next = n5; n5 ->next =n6;n6 ->next = n7;

    MyLinklist myLinklist;
    myLinklist.printNodes(h1);
//    myLinklist.printNodes(myLinklist.reverseList(h1));
//    myLinklist.printNodes(myLinklist.reverseListBetween(h1 ,2 ,5));
//    myLinklist.printNodes(myLinklist.reverseListBetween(h1 ,2 ,7));
//    myLinklist.printNodes(myLinklist.reverseListBetween(h1 ,1 ,7));

    ListNode *h2 = new ListNode(10);
    ListNode *n2_2 = new ListNode(11);
    ListNode *n3_2 = new ListNode(5);
    ListNode *n4_2 = new ListNode(4);


    /* test getIntersection */
//    h2->next = n2_2; n2_2 ->next = n3_2; n3_2 ->next = n3;
//    myLinklist.printNodes(h2);

//    cout << myLinklist.getIntersectionNodeSet(h1,h2) ->val << endl;
//    cout << myLinklist.getIntersectionNodeOn1(h1,h2) ->val << endl;

    /* test cycle*/
//    n7->next = n4;
//    cout << myLinklist.detectCycleFastSlowPointer(h1) ->val << endl;
//    cout << myLinklist.detectCycleSet(h1) ->val << endl;


    /* test partion */
//    h1 -> next = n4; n4 ->next = n3; n3 ->next = n2; n2 ->next =n5;
//    myLinklist.printNodes(myLinklist.partition(h1 , 3) );
    return 0;
}
