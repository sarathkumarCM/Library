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
    int diameterOfBinaryTree(TreeNode* root) {
        if(root==nullptr)
        return 0;
        int lh=dfs(root->left);
        int rh=dfs(root->right);
        
        int ml=diameterOfBinaryTree(root->left);
        int mr=diameterOfBinaryTree(root->right);

        return max({lh+rh,ml,mr}); /// max of set of elements 
    }
};


//best 
class Solution {
public:
int mx=0;
    
    int solve(TreeNode* root){
         if(root==NULL)return 0;
        int lh=solve(root->left);
        int rh=solve(root->right);
        mx=max(mx,lh+rh);
        return 1+max(lh,rh);
    }



    int diameterOfBinaryTree(TreeNode* root) {
        //how can i reach the farthest nodes 
        //find the node at maximum height
        //if(root==NULL)return 0;
       solve(root);
       return mx;
        
        

        
    }
};

//secnd
class Solution {
public:
      int findmax(TreeNode* root , int  & daimeter){
         if(root == NULL) return 0 ;

         int lh = findmax(root->left , daimeter) ;
         int rh = findmax(root->right , daimeter) ;

         daimeter = max(daimeter , lh + rh) ;


        return 1 + max(lh , rh ) ;
      }
      int diameterOfBinaryTree(TreeNode* root) {
      int daimeter = 0 ;

      findmax(root ,daimeter) ;

      return daimeter ;
    }
};
