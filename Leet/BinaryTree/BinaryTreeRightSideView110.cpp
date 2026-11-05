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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        queue<TreeNode *> q;
        if(root!=nullptr){
            q.push(root);
        }
        while(!q.empty()){
            int sz=q.size();
            TreeNode *itm=q.back();
            ans.push_back(itm->val);
            for(int i=0;i<sz;i++){
                TreeNode *nd=q.front();
                q.pop();
                if(nd->left) q.push(nd->left);
                if(nd->right) q.push(nd->right);
            }
        }
        return ans;
    }
};

//another 
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> retval;

        if (root == NULL) return retval;

        queue<TreeNode *> q;

        q.push(root);

        while (!q.empty()) {
            bool should_add_to_retval = true;
            size_t q_size = q.size();

            for (size_t i = 0; i < q_size; ++i) {
                TreeNode * cur = q.front();
                q.pop();
                if (should_add_to_retval) retval.push_back(cur->val);
                should_add_to_retval = false;
                if (cur->right != NULL) q.push(cur->right);
                if (cur->left != NULL) q.push(cur->left);
            }
        }

        return retval;
    }
};