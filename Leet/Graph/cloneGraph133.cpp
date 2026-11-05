#include<bits/stdc++.h>

using namespace std;
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


class Solution {
public:

    Node* cloneGraph(Node* node) {
        if(node==nullptr){
            return nullptr;
        }
        if(!visited[node->val]){
            
            Node *newNode=new Node(node->val);
            visited[node->val]=newNode;
            cout<<"Node "<<newNode->val<<endl<<" Neighbours: "<<endl;
            for(auto &it:node->neighbors){
                Node *tt=cloneGraph(it);
                newNode->neighbors.push_back(tt);
                cout<<" "<<tt->val;
                //cloneGraph(it);
            }
            return newNode;
        }else{
            return visited[node->val];
        }
        return nullptr;
    }
    unordered_map<int,Node*> visited;
}; //-- best soln


class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


class Solution2 {
private:
    Node* dfs(Node* node, unordered_map<Node*, Node*>& hashmap){
        Node* newNode = new Node(node->val);
        hashmap[node] = newNode;
        for(Node* nbrNode : node->neighbors){
            Node* newNbrNode = hashmap.count(nbrNode) ? hashmap[nbrNode] : dfs(nbrNode, hashmap);
            newNode->neighbors.push_back(newNbrNode);
        }

        return newNode;
    }

public:
    Node* cloneGraph(Node* node) {
        if(!node) return nullptr;
        unordered_map<Node*, Node*> hashmap;
        return dfs(node, hashmap);
    }
};


int main(){
    Solution s;

    Node * ans=new Node(20);
    Node* res=s.cloneGraph(ans);

}