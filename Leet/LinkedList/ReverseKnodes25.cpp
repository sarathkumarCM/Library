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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *thead=head;
        int cnt=0;
        while (thead!=nullptr){
            cnt++;
            thead=thead->next;
        }
        ListNode *begin=head,*cur=head,*nd=head, *prev=nullptr;
        int curCount=0;
        int i=0;
        while(cur!=nullptr && curCount< (cnt - (cnt%k))){
            //reverse till k
            while(i<k){
                if(i==0)
                    nd=cur;
                ListNode *nxt=cur->next;
                cur->next=prev;
                prev=cur;
                cur=nxt;
                i++;
                curCount++;
            }
            if(curCount<=k){
                head=prev;
                begin=nd;
            }else{
                begin->next=prev;
                begin=nd;
            }
            nd->next=cur; //point start to start of next series;
            prev=nd;
            i=0;
        }   
        return head;
    }
};

int main(){
    int n,k;
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
    cin>>k;
    Solution s;
    ListNode *res=s.reverseKGroup(head,k);

}

//another one
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1) return head;

        ListNode dummy(0);
        dummy.next = head;

        ListNode* prevGroup = &dummy;

        while (true) {
            ListNode* kth = prevGroup;
            for (int i = 0; i < k && kth; i++) {
                kth = kth->next;
            }
            if (!kth) break;

            ListNode* groupNext = kth->next;

            ListNode* prev = groupNext;
            ListNode* curr = prevGroup->next;

            while (curr != groupNext) {
                ListNode* nextNode = curr->next;
                curr->next = prev;
                prev = curr;
                curr = nextNode;
            }

            ListNode* temp = prevGroup->next;
            prevGroup->next = kth;
            prevGroup = temp;
        }

        return dummy.next;
    }
};

//recursion
class Solution
{
public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *temp = head;
        int cnt = 0;
        // check if k node exist
        while (cnt < k)
        {
            if (temp == NULL)
            {
                return head;
            }
            temp = temp->next;
            cnt++;
        }

        // recursively call for rest of LL
        ListNode *prevNode = reverseKGroup(temp, k);

        // reverse current group
        temp = head;
        cnt = 0;
        while (cnt < k)
        {
            ListNode *next = temp->next;
            temp->next = prevNode;

            prevNode = temp;
            temp = next;

            cnt++;
        }

        return prevNode;
    }
};


class Solution {
public:
    int count ( ListNode *head ){
        int count = 0;
        while ( head != nullptr){
            head = head->next;
            count ++ ;
        }
        return count ;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        if( head == nullptr || head->next == nullptr || count(head) < k) return head;
        int cnt = k;
        ListNode *curr = head ;
        ListNode *prev = nullptr;
        ListNode *next = nullptr;
        while( curr != nullptr && cnt > 0){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
            cnt--;
        }
        head -> next = reverseKGroup(next,k);
        return prev;

        
    }
};
int init = [] {
    ofstream out("user.out");
    cout.rdbuf(out.rdbuf());
    vector<int> nums;
    nums.reserve(5000);
    for (string str, k_str; getline(cin, str) && getline(cin, k_str);
         cout << '\n') {
        stringstream ss(str.substr(1, str.size() - 2));
        const int k = stoi(k_str);
        nums.clear();
        for (int i; ss >> i;) {
            nums.push_back(i);
            if (ss.peek() == ',')
                ss.ignore();
        }
        const int n = (nums.size() / k) * k;
        for (int i = 0; i < n; i += k) {
            reverse(nums.begin() + i, nums.begin() + i + k);
        }
        cout << '[';
        copy(nums.begin(), nums.end() - 1, ostream_iterator<int>(cout, ","));
        cout << nums.back() << ']';
    }
    exit(0);
    return 0;
}();