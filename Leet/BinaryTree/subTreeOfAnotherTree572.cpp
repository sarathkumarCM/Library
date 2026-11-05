/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q){
        if(p==nullptr && q==nullptr) return true;
        if(p==nullptr) return false;
        if(q==nullptr) return false;
        if(p->val!=q->val){
            return false;
        }
        bool stat=isSameTree(p->left,q->left);
        bool stat2=isSameTree(p->right,q->right);
        return stat&stat2;
    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(root==nullptr && subRoot==nullptr){
            isS=true;
            return true;
        }
        if(root==nullptr){
            return false;
        }
        bool st1=isSameTree(root,subRoot);
        if(st1){
            return true;
        }
        bool st2=isSubtree(root->left, subRoot);
        bool st3 = isSubtree(root->right, subRoot);
        return (st1||st2||st3);
    }
    bool isS=false;
};

//best -- same shit
class Solution {
public:
    bool compare(TreeNode*root,TreeNode*subRoot)
    {
        if(root==nullptr&&subRoot==nullptr) return true;
        if(root==nullptr||subRoot==nullptr||root->val!=subRoot->val) return false;
        return compare(root->left,subRoot->left)&&compare(root->right,subRoot->right);
    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(root==nullptr) return false;
        return compare(root,subRoot)||isSubtree(root->left,subRoot)||isSubtree(root->right,subRoot); 
    }
};