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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        queue<TreeNode *> q;
        if(root!=nullptr){
            q.push(root);
        }
        while(!q.empty()){
            vector<int> tans;
            int sz= q.size();
            for(int i=0;i<sz;i++){
                TreeNode *tmp=q.front();
                q.pop();
                if(tmp!=nullptr){
                    tans.push_back(tmp->val);
                }
                if(tmp->left!=nullptr) q.push(tmp->left);
                if(tmp->right!=nullptr) q.push(tmp->right);
            }
            ans.push_back(tans);
        }
        return ans;

    }
};

//best
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        
        vector<vector<int>> ans;
        
        if(root == NULL)
            return ans;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while(!q.empty()) {
            
            int size = q.size();
            vector<int> level;
            
            for(int i = 0; i < size; i++) {
                
                TreeNode* temp = q.front();
                q.pop();
                
                level.push_back(temp->val);
                
                if(temp->left)
                    q.push(temp->left);
                
                if(temp->right)
                    q.push(temp->right);
            }
            
            ans.push_back(level);
        }
        
        return ans;
    }
};