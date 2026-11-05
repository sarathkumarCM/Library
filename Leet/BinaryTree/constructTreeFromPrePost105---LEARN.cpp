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

    TreeNode* bT(unordered_map<int,int> &mp,vector<int> &preOrder, int &preIndex, int left, int right){
        if(left>right)
            return nullptr;
        int rootVal=preOrder[preIndex];
        TreeNode *root=new TreeNode(rootVal);
        preIndex++;
        int index=mp[rootVal];
        root->left=bT(mp,preOrder,preIndex,left, index-1);
        root->right=bT(mp,preOrder,preIndex,index+1, right);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int,int> mp;
        for(int i=0;i<inorder.size();i++){
            mp[inorder[i]]=i;
        }
        int preIndex=0;
        return bT(mp,preorder,preIndex,0, inorder.size()-1);
    }   
};

//learn thisss

//best

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inorderMap;
        for(int i = 0; i < inorder.size(); i++){
            inorderMap[inorder[i]] = i;
        }
        int preorderIndex = 0;
        return build(preorder, preorderIndex, 0, inorder.size() - 1, inorderMap);
    }
    TreeNode* build(vector<int>& preorder, int &preorderIndex, int inorderStart, int inorderEnd, unordered_map<int, int>& inorderMap){
        if(inorderStart > inorderEnd){
            return NULL;
        }
        int rootval = preorder[preorderIndex];
        preorderIndex++;
        TreeNode* root = new TreeNode(rootval);
        int inorderIndex = inorderMap[rootval];
        root->left = build(preorder, preorderIndex, inorderStart, inorderIndex-1, inorderMap);
        root->right = build(preorder, preorderIndex, inorderIndex+1, inorderEnd, inorderMap);
        return root;
    }
};