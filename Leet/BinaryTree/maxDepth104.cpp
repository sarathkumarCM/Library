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

int dfs(TreeNode *root){
    if (root==nullptr){
        return 0;
    }
    return 1+ max(dfs(root->left),dfs(root->right));
}   
class Solution {
public:
    int maxDepth(TreeNode* root) {
        return dfs(root);
    }
};

//best 
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root==NULL) return 0;
        return max(maxDepth(root->left),maxDepth(root->right))+1;
    }
};