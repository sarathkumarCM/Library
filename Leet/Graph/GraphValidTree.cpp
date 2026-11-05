#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool dfs(int parent, int node, unordered_map<int,vector<int>> &adj, vector<bool> &vis){
        vis[node]=true;
        for(auto &it:adj[node]){
            if(!vis[it]){
                if(!dfs(node,it,adj,vis)){
                    return false;
                }
            }else{
                if(it!=parent){ // if visited and a non parent comes in  :/
                    return false;
                }
            }
        }
        return true;
    }
    bool dfs2(int parent, int node, unordered_map<int,vector<int>> &adj, vector<bool> &vis){
        if(vis[node]){
            return false;
        }
        vis[node]=true;
        for(auto &it:adj[node]){
            if(it==parent)
                continue;
            dfs(node, it,adj,vis);
        }
        return true;
    }
    bool validTree(int n, vector<vector<int>>& edges) {
        unordered_map<int,vector<int>> adj;
        for(auto &it:edges){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        vector<bool> vis(n,false);
        if(!dfs(-1,0,adj,vis)){
            return false;
        }
        for(int i=0;i<n;i++){
            if(vis[i]==false){
                return false;
            }
        }
        return true;
    }
};

int main(){
    int n;
    cin>>n;
    int m;
    cin>>m;
    vector<vector<int>> inp;
    for(int i=0;i<m;i++){
        vector<int> inp1(2);
        cin>>inp1[0]>>inp1[1];
        inp.push_back(inp1);
        
    }
    Solution s;
    cout<<s.validTree(n,inp);

}

//Best
class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() > n -1)
            return false;
        
        vector<vector<int>> adj(n);

        for (const auto& edge: edges)
        {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        unordered_set<int> visit;

        if (!dfs(0, -1, visit, adj))
        {
            return false;
        }

        return visit.size() == n;
    }

    private: 
        bool dfs(int node, int parent, 
                 unordered_set<int>& visit,
                 vector<vector<int>>& adj)
        {
            // cycle detected.
            if (visit.count(node))
                return false;

            visit.insert(node);
            for (int nei : adj[node])
            {
                if (nei == parent)
                    continue;
                
                if (!dfs(nei, node, visit, adj))
                    return false;
            }
            
            return true;
        }
};

//easy af 
bool dfs2(int parent, int node, unordered_map<int,vector<int>> &adj, vector<bool> &vis){
        if(vis[node]){
            return false;
        }
        vis[node]=true;
        for(auto &it:adj[node]){
            if(it==parent)
                continue;
            if(!dfs2(node, it,adj,vis))
                return false;
        }
        return true;
    }
