#include<bits/stdc++.h>

using namespace std;


 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
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
    ListNode *res=s.reverseList(head);
}