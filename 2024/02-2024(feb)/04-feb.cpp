//{ Driver Code Starts
//Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// Node Class
class Node {
public:
    int data;
    Node* next;

    Node(int val) : data(val), next(NULL) {}
};

// Linked List Class
class LinkedList {
public:
    Node* head;
    Node* tail;

    LinkedList() : head(NULL), tail(NULL) {}

    // creates a new node with given value and appends it at the end of the linked list
    void insert(int val) {
        if (head == NULL) {
            head = new Node(val);
            tail = head;
        } else {
            tail->next = new Node(val);
            tail = tail->next;
        }
    }
};


// } Driver Code Ends
//User function Template for C++

class Solution {
public:

    int length(Node* head){
        int size=0;
        while(head){
            size++;
            head=head->next;
        }
        return size;
    }
    
    Node* paddZeroes(Node* sHead, int diff){
        Node* zHead = new Node(0);
        Node* temp = zHead;
        diff--;
        while(diff--){
            temp->next = new Node(0);
            temp = temp->next;
        }
        
        temp->next = sHead;
        
        return zHead;
    }
    
    Node* subHelper(Node* l, Node* s, bool& borrow){
        if(l==NULL&&s==NULL&&!borrow){
            return NULL;
        }
        
        Node* prev = subHelper(l->next, s->next, borrow);
        
        int a = l->data;
        int b = s->data;
        
        if(borrow){
            a--;
            borrow = false;
        }
        
        if(a<b){
            a = a+10;
            borrow = true;
        }
        
        int diff = a-b;
        
        Node* curr = new Node(diff);
        
        curr->next = prev;
        
        return curr;
    }

    Node* subLinkedList(Node* head1, Node* head2) {
        if(head1==NULL && head2==NULL){
            return NULL;
        }
        
        Node* temp1 = head1;
        Node* temp2 = head2;
        
        while(head1!=NULL&&head1->data==0){
            head1 = head1->next;
        }
        
        while(head2!=NULL && head2->data==0){
            head2 = head2->next;
        }
        
        int len1 = length(head1);
        int len2 = length(head2);
        //cout<<len1;
        Node* sHead = NULL;
        Node* lHead = NULL;
        
        temp1 = head1;
        temp2 = head2;
        
        if(len1!=len2){
            sHead = len1<len2 ? head1 : head2;
            lHead = len1>len2 ? head1 : head2;
            sHead = paddZeroes(sHead, abs(len1-len2));
        }
        else{
            while(temp1!=NULL&&temp2!=NULL){
                int a = temp1->data;
                int b = temp2->data;
                if(a!=b){
                    sHead = a<b ? head1 : head2;
                    lHead = a>b ? head1 : head2;
                    break;
                }
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
        }
        
            
        
        
        if(!temp1&&!temp2){
            return new Node(0);
        }
        
        bool borrow= false;
        
        Node* ans = subHelper(lHead,sHead,borrow);
        
        while(ans && ans->data==0){
            ans = ans->next;
        }
        
        return ans;
    }
};

//{ Driver Code Starts.

// prints the elements of linked list starting with head
void printList(Node* n) {
    while (n) {
        cout << n->data;
        n = n->next;
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        int n;
        cin >> n;
        LinkedList LL1;
        string l1,l2;
        cin>>l1;
        for (int j = 0; j < n; ++j) {
            int x=(l1[j]-'0');
            LL1.insert(x);
        }

        int m;
        cin >> m;
        LinkedList LL2;
        cin>>l2;
        for (int j = 0; j < m; ++j) {
            int x=(l2[j]-'0');
            LL2.insert(x);
        }

        Solution ob;
        Node* res = ob.subLinkedList(LL1.head, LL2.head);
        printList(res);
    }

    return 0;
}

// } Driver Code Ends
