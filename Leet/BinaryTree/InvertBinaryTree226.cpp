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
        TreeNode* invertTree(TreeNode* root) {
            if(root==nullptr){
                return nullptr;
            }
            if(root->left!=nullptr){
                invertTree(root->left);
            }
            if(root->right!=nullptr){
                invertTree(root->right);
            }
            TreeNode *temp=root->left;
            root->left=root->right;
            root->right=temp;
            return root;
            
        }
};


void inOrder(TreeNode *root){
    if(root!=nullptr){
        inOrder(root->left);
        cerr<<" "<<root->val;
        inOrder(root->right);
    }
}
void fillBtree(TreeNode *&root, vector<int> &bt,int idx, int n){
    if(idx>=n){
        return;
    }
    root=new TreeNode(bt[idx]);
    fillBtree(root->left,bt,(2*idx+1),n);
    fillBtree(root->right,bt,(2*idx+2),n);
}

int main(){
    int n,t;
    cin>>n;
    vector<int> bt(n);
    TreeNode *root=nullptr;
    int rt=0;
    for(auto &it:bt){
        cin>>it;
    }
    fillBtree(root,bt,0,n);
    inOrder(root);
    cerr<<endl;
    Solution s;
    TreeNode *root2=s.invertTree(root);
    inOrder(root2);

}

//best
 TreeNode* invertTree(TreeNode* root) {
        if(root==NULL) return NULL;
        swap(root->left,root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }

