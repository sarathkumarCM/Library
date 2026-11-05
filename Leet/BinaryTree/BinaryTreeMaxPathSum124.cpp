#include<bits/stdc++.h>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


class Solution {
public:
    int dfs(TreeNode *root){
        if(root==nullptr)
            return 0;
        int vl=dfs(root->left);
        int vr=dfs(root->right);
        int mx=max({root->val, root->val+vl, root->val+vr});
        maxm=max({maxm,mx, root->val+vl+vr});
        return mx;
    }
    int maxPathSum(TreeNode* root) {
        int sm=0;
        if(root!=nullptr)
            sm=dfs(root);
        return maxm;
    }
    int maxm=-100005;
};

 void inOrder(TreeNode *root){
    if(root!=nullptr){
        inOrder(root->left);
        cerr<<" "<<root->val;
        inOrder(root->right);
    }
}
void fillBtree(TreeNode *&root, vector<string> &bt,int idx, int n){
    if(idx>=n){
        return;
    }
    if(bt[idx]=="null"){
        return;
    }
    int val=atoi(bt[idx].c_str());
    root=new TreeNode(val);
    fillBtree(root->left,bt,(2*idx+1),n);
    fillBtree(root->right,bt,(2*idx+2),n);
}

int main(){
    int n,t;
    cin>>n;
    vector<string> bt(n);
    TreeNode *root=nullptr;
    int rt=0;
    for(auto &it:bt){
        cin>>it;
    }
    fillBtree(root,bt,0,n);
    //cerr<<"done filling"<<endl;
    inOrder(root);
    //cerr<<endl;
    Solution s;
    int sum=s.maxPathSum(root);
    cout<<sum<<endl;
    

}


//best
class Solution2 {
private:
    int computeMaxPath(TreeNode* node, int& maxPathSum) {
        if (node == NULL)
            return 0;
        int LS = max(0, computeMaxPath(node->left, maxPathSum)); //i.e negative hua toh lena hi nahi hai
        int RS = max(0, computeMaxPath(node->right, maxPathSum));

        maxPathSum = max(maxPathSum, LS + RS + node -> val); 
        /* agar LS ya RS mein se koi -ve hua toh woh anyways include nahi hoge, it would return 0 -- in case both LS, RS are -ve, only return root*/
        return node -> val + max(LS, RS);
    }

public:
    int maxPathSum(TreeNode* root) { 
        int maxPathSum = INT_MIN;
        computeMaxPath(root, maxPathSum);
        return maxPathSum;
        
    }
};