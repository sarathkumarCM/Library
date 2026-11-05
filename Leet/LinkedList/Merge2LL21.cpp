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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        
        if(list1==nullptr)
            return list2;
        if(list2==nullptr)
            return list1;
        
        if(list1->val>list2->val)
            swap(list1,list2);

        ListNode *tl1=list1,*tl2=list2, *prev1=nullptr, *prev2=nullptr;
        ListNode *tlt=tl1;

        while(tl2!=nullptr || tl1!=nullptr){
            //cerr<<"Testing"<<endl;
            if(tl2==nullptr){
                break; // exit no need to do anything
            }
            if (tl1->next==nullptr){
                if(tl1->val<=tl2->val){
                    tl1->next = tl2; //point to the second list :D
                    break;
                }
            }
            if(tl1->val <= tl2->val){
                prev1=tl1;
                tl1=tl1->next;
            }else{
                prev1->next=tl2;
                prev2=tl2;
                tl2=tl2->next;
                prev2->next=tl1;
                prev1=prev2;
                
            }
        }

        return list1;
    }
};

/*

1 4 5 6
2 7 9

1 2 3 4
5 6

1 4 5
2 3

.
2 4

2 3
.

2 3 4
1 4

1 4
2 3 4

*/

int main(){
    int m,n;
    cin>>m>>n;
    ListNode *list = new ListNode();
    ListNode *head=nullptr,*cur, *head2=nullptr;
    int t;
    for(int i=0;i<m;i++){
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
    for(int i=0;i<n;i++){
        cin>>t;
        if(i==0){
            head2=new ListNode(t);
            cur=head2;
        }else{
            ListNode *tmp=new ListNode(t);
            cur->next=tmp;
            cur=tmp;
        }
    }
    Solution s;
    ListNode *res=s.mergeTwoLists(head,head2);
    //cerr<<"here"<<endl;
    while(res!=nullptr){
        cout<<res->val<<" ";
        res=res->next;
    }
    //cout<<endl;
}


class Solution2 {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(list1==nullptr) return list2;
        if(list2==nullptr) return list1;
        //comparison
        if(list1->val < list2->val){
            list1->next= mergeTwoLists(list1->next,list2);
            return list1;
        } else{
            list2->next= mergeTwoLists(list1,list2->next);
            return list2;

        }
        
    }
};
