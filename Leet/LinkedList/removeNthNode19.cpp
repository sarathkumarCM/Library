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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *tHead=head;
        int cnt=0;
        while(tHead!=nullptr){
            tHead=tHead->next;
            cnt++;
        }
        
        int remove=cnt-n;
        //cerr<<" cnt "<<cnt<<" remove "<<remove<<endl;
        tHead=head;
        int cn=0;
        if(remove==0){
            head=head->next;
            return head;
        }
        while(cn<=remove && tHead!=nullptr){
            if(cn+1==remove){
                //cerr<<"Remove "<<tHead->next->val<<endl;
                tHead->next=tHead->next->next;
                break;
            }
            tHead=tHead->next;
            cn++;
        }

        // cerr<<"here "<<endl;
        // while(head!=nullptr){
        //     cout<<head->val<<" ";
        //     head=head->next;
        // }
        return head;
    }
};

class Solution2 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* fast = head;
        ListNode* slow = head;

        // Step 1: fast ko n steps aage le jao
        for(int i = 0; i < n; i++) {
            fast = fast->next;
        }

        // Edge case: agar first node hi remove karna ho
        if(fast == nullptr) {
            return head->next;
        }

        // Step 2: dono ko saath move karo
        while(fast->next != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        // Step 3: delete nth node from end
        slow->next = slow->next->next;

        return head;
    }
};

int main(){
    int n,m;
    cin>>n>>m;
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
    ListNode *res=s.removeNthFromEnd(head,m);
}