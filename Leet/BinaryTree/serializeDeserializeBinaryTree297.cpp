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

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res="";
        queue<TreeNode *> q;
        if(root!=nullptr){
            q.push(root);
        }
        
        while(!q.empty()){
            TreeNode *nd=q.front();
            q.pop();
            if(nd){
                if(res=="")
                    res+=to_string(nd->val);
                else{
                    res+=","+to_string(nd->val);
                }
                q.push(nd->left);
                q.push(nd->right);
            }else{
                res+=",null";
            }
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data=="null"|| data.empty()) return nullptr;
        char delim=',';
        string token;
        stringstream ss(data);
        getline(ss,token,delim);
        TreeNode *root=new TreeNode(stoi(token));
        queue<TreeNode *> q;
        q.push(root);
        while(!q.empty()){
            TreeNode *tr=q.front();
            q.pop();
            if(!getline(ss,token,delim)) break;
            if(token!="null"){
                TreeNode *tmp=new TreeNode(stoi(token));
                tr->left=tmp;
                q.push(tmp);
            }
            if(!getline(ss,token,delim)) break;
            if(token!="null"){
                TreeNode *tmp=new TreeNode(stoi(token));
                tr->right=tmp;
                q.push(tmp);
            }
        }
        return root;
    }
};

int main(){
    Codec ser,deser;
    string s;
    cin>>s;
    string s2= ser.serialize(deser.deserialize(s));
    cout<<s2<<endl;
}