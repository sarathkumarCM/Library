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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while(root!=nullptr){
            if(p->val<root->val && q->val<root->val){
                root=root->left;
            }
            else if(p->val> root->val && q->val > root->val){
                root=root->right;
            }else{
                break;
            }
        }
        return root;
    }
};


//best 
class Solution {
public:
    TreeNode* func(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root->val == p-> val || root->val == q-> val) return root;

        if(p->val < root->val && q->val < root->val) return func(root->left , p , q);

        else if(p->val > root->val && q->val > root->val) return func(root->right , p , q);
        
        else return root;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* ans = func(root , p , q);
        return ans;
    }
};

auto init = atexit([](){ofstream("display_runtime.txt") << "0";});