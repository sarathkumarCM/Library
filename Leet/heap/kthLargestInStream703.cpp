#include<bits/stdc++.h>
using namespace std;

class KthLargest2 {
public:
    KthLargest(int k, vector<int>& nums) {
        kv=k;
        for(auto &it:nums){
            marks.push(it);
        }
    }
    
    int add(int val) {
        marks.push(val);
        priority_queue<int> test(marks);
        for(int i=1;(!test.empty())&&(i<kv);i++){
            test.pop();
        }
        return test.top();
    }
    priority_queue<int> marks;
    int kv=0;
}; // timeout 

class KthLargest1 {
public:
    KthLargest(int k, vector<int>& nums) {
        kv=k;
        for(auto &it:nums){
            marks.emplace_back(it);
        }
    }
    
    int add(int val) {
        marks.emplace_back(val);
        nth_element(marks.begin(),marks.begin()+(kv-1), marks.end(),greater<int>());
        return marks[kv-1];
    }
    vector<int> marks;
    int kv=0;
}; // -- best timing out too

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class KthLargest4 {
public:

    void insert(TreeNode *&root, int val){
        TreeNode *nn=new TreeNode(val);
        if(root==nullptr){
            root=nn;
        }else{
            if(val>root->val){
                insert(root->right,val);
            }else if(val<root->val){
                insert(root->left,val);
            }
        }
    }

    KthLargest(int k, vector<int>& nums) {
        kv=k;
        for(auto &it:nums){
            insert(root,it);
        }
    }
    void postOrder(TreeNode *&root,int cur){
        if(cur>=kv){
            fnd=root->val;
            cout<<"fnd "<<root->val;
            return;
        }
        postOrder(root->right,cur+1);
        postOrder(root->left,cur+1);
        cur+=1;

    }
    
    int add(int val) {
        //marks.emplace_back(val);
        insert(root,val);
        postOrder(root,0);
        return marks[kv-1];
    }
    int kv=0;
    int fnd=INT_MIN;
    TreeNode *root=nullptr;
};

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
        kv=k;
        for(auto &it:nums){
            int a=add(it);
        }
    }
    
    int add(int val) {
        marks.push(val);
        if(marks.size()>kv){
            marks.pop();
        }
        return marks.top();
    }
    priority_queue<int,vector<int>,greater<int>> marks;
    int kv=0;
};

//best

class KthLargestB {
public:
    priority_queue<int,vector<int>,greater<int>> topK; 
    int k;
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for(int num:nums){
            this->topK.push(num);
            if(this->topK.size()==k+1){
                this->topK.pop();
            }
        }
    }
    
    int add(int val) {
        this->topK.push(val);
        if(this->topK.size()==this->k+1) this->topK.pop();
        return this->topK.top();
    }
};

//better
class KthLargest {
private:
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int k;

public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;

        for (int num : nums) {
            add(num);
        }
    }

    int add(int val) {
        // Add to our minHeap if we haven't processed k elements yet
        // or if val is greater than the top element (the k-th largest)
        if (minHeap.size() < k || minHeap.top() < val) {
            minHeap.push(val);
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        return minHeap.top();
    }
};




/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

 int main(){

 }