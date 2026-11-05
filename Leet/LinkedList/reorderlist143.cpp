#include<bits/stdc++.h>

using namespace std;


 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution2 {
public:
    ListNode* reverseList(ListNode* head) {
        if(head==nullptr){
            return nullptr;
        }else{
        
            ListNode *tHead=head, *prev=nullptr;

            while(head!=nullptr){
                ListNode *nxt =  head->next;
                head->next=prev;
                prev=head;
                head=nxt;
            }
            head=prev;
        }

        return head;
    }
};

class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode* tHead=head, *rev=head;
        //reverse llist
        stack<ListNode *> revStack;
        int size=0;
        while(rev!=nullptr){
            revStack.push(rev);
            rev=rev->next;
            size++;
        }
        while(revStack.size()>(size/2)){
            //cerr<<"Head "<<tHead->val;
            ListNode *nxt=tHead->next;
            tHead->next=revStack.top();
            //cerr<<", Revstack top "<<revStack.top()->val<<endl;
            revStack.top()->next=nxt;
            revStack.pop();
            if(tHead->next!=nullptr)
                tHead=tHead->next->next;
            
        }
        tHead->next=nullptr;
        // cerr<<"here?"<<endl;
        while(head!=nullptr){
            cout<<head->val<<" ";
            head=head->next;
        }

    }
};

//smart
class Solution2 {
public:
    void reorderList(ListNode* head) {
        // approach:
        // 1. find midpoint of list
        // 2. reverse second half of list and add a pointer to the tail node
        // 3. increment head and tail pointers and merge nodes
        
        if (!head || !head->next || !head->next->next) return;

        // 1. find midpoint and split
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* midpoint = slow->next;
        slow->next = nullptr;

        // 2. reverse second half (must start at midpoint)
        ListNode* prev_node = nullptr;
        ListNode* curr_node = midpoint;

        while (curr_node != nullptr) {
            ListNode* next_node = curr_node->next;
            curr_node->next = prev_node;
            prev_node = curr_node;
            curr_node = next_node;
        }

        ListNode* tail = prev_node;

        // 3. merge
        ListNode* front = head;
        ListNode* back = tail;

        while (back != nullptr) {
            ListNode* front_next = front->next;
            ListNode* back_next = back->next;

            front->next = back;
            back->next = front_next;

            front = front_next;
            back = back_next;
        }
    }
};

int main(){
    int n;
    cin>>n;
    ListNode *list = new ListNode();
    ListNode *head,*cur;
    int t;
    for(int i=0;i<n;i++){
        cin>>t;
        if(i==0){
            head=new ListNode(t);
            cur=head;
        }else{
            ListNode *tmp=new ListNode(t);
            cur->next=tmp;
            cur=tmp;
        }
    }
    Solution s;
    s.reorderList(head);
}