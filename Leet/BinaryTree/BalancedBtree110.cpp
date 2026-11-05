 int maxDepth(TreeNode* root) {
        if(root==NULL) return 0;
        return max(maxDepth(root->left),maxDepth(root->right))+1;
}
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(root==nullptr){
            return balanced;
        }
        int lh=maxDepth(root->left);
        int rh=maxDepth(root->right);
        if(abs(lh-rh)>1){
            balanced=false;
        }

        isBalanced(root->left);
        isBalanced(root->right);
        return balanced;
    }
    bool balanced=true;
};


//best
class Solution {
public:
    pair<int,bool> solve(TreeNode* root){
        if(!root){
            return {0,true};
        }
        pair<int,bool> left=solve(root->left);
        pair<int,bool> right=solve(root->right);
        if(left.second==true && right.second==true && abs(left.first-right.first)<=1) return {1+max(left.first,right.first),true};
        else return {1+max(left.first,right.first)
        ,false};
    }
    bool isBalanced(TreeNode* root) {
        pair<int,bool> ans=solve(root);
        return ans.second;
    }
};



