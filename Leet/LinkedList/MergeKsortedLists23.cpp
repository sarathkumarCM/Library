#include<bits/stdc++.h>

using namespace std;


 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

 vector<int> ans;
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
    
    //cheated
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ans.clear();
        for(auto &it: lists){
            while(it!=nullptr){
                ans.push_back(it->val);
                ListNode *tmp=it;
                it=it->next;
                delete tmp;
            }
            
        }
        sort(ans.begin(),ans.end());
        ListNode *nxt= nullptr;
        ListNode *head=nullptr;
        
        for(auto &it:ans){
            cout<<it<<" ";
            ListNode *newNode=new ListNode(it);
            if(nxt==nullptr){
                head=newNode;
                nxt=newNode;
            }else{
                nxt->next=newNode;
                nxt=newNode;
            }
        }
        return head;
    }
};



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


//heap
class Solution {
public:
    struct Comparison {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* res = new ListNode(0);
        ListNode* current = res;
        priority_queue<ListNode*, vector<ListNode*>, Comparison> min_heap;
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i]) {
                min_heap.push(lists[i]);
            }
        }
        while (!min_heap.empty()) {
           ListNode* node = min_heap.top();
           min_heap.pop();
           current->next = node;
           current = current->next;
           if (node->next) min_heap.push(node->next);
        }
        return res->next;
    }
};
//vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end()); - remove all null
//mine better
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        lists.erase(
            std::remove(lists.begin(), lists.end(), nullptr),
            lists.end()
        ); // -- remove empty lists -- smart!@!!!!
        if (empty(lists)) {
            return nullptr;
        }
        std::sort(lists.begin(), lists.end(), [] (ListNode* a, ListNode* b) {
            return a->val > b->val;
        });
        ListNode* ret = nullptr;
        ListNode* cursor = nullptr;

        ret = lists.back();
        if (lists.back()->next) {
            lists[lists.size()-1] = lists.back()->next;
            std::rotate(std::find_if(lists.begin(), lists.end()-1, [&lists] (ListNode* x) { return x->val < lists.back()->val; }), lists.end()-1, lists.end());
            //Efficient partial reorder
        } else {
            lists.pop_back();
        }
        
        cursor = ret;
        while (!lists.empty()) {
            cursor->next = lists.back();
            if (lists.back()->next) {
                lists[lists.size()-1] = lists.back()->next;
                std::rotate(std::find_if(lists.begin(), lists.end()-1, [&lists] (ListNode* x) { return x->val < lists.back()->val; }), lists.end()-1, lists.end());
            } else {
                lists.pop_back();
            }
            cursor = cursor->next;
        }
        return ret;
    }
};