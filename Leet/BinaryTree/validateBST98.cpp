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
    void dfs(TreeNode* root, long long maxVal, long long minVal){
        if(root==nullptr){
            return ;
        }
        if(root->val<=minVal){
            isGood=false;
            return;
        }
        if(root->val>=maxVal){
            isGood=false;
            return;
        }
        if(root->left!=nullptr){
            if(root->val <= root->left->val){
                isGood=false;
                return;
            }
        }
        if(root->right!=nullptr){
            if(root->val>root->right->val){
                isGood=false;
                return;
            }
        }
        dfs(root->left,root->val,minVal);
        dfs(root->right,maxVal, root->val);
    }
    bool isValidBST(TreeNode* root) {
        long long maxVal=LONG_MAX,minVal=LONG_MIN;
        dfs(root,maxVal,minVal);
        return isGood;
    }
    bool isGood=true;
};

//best
class Solution {
public:
    bool validRange(TreeNode* root , long min ,long max){
        if(root == NULL){
            return true;
        }
        if(root->val <= min || root->val >= max){
            return false;
        }
        bool leftBst = validRange(root->left ,  min , root->val);
        bool rightBst = validRange(root->right , root->val, max);
        return leftBst && rightBst;
    }

    bool isValidBST(TreeNode* root) {
        return validRange(root,LONG_MIN,LONG_MAX);
    }
};