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

    void inOrder(TreeNode* root, int k){
        if(root==nullptr)
            return;
        inOrder(root->left,k);
        cnt++;
        if(cnt==k){
            kth=root->val;
        }
        inOrder(root->right,k);
    }
    int kthSmallest(TreeNode* root, int k) {
        inOrder(root,k);
        return kth;
    }
    int cnt=0;
    int kth=-1;
};

//best - same as me