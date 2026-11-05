#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool dfs(int node, unordered_map<int,vector<int>> &edges, vector<bool> &vis,unordered_set<int> &path){
        if(path.find(node)!=path.end()){ // cycle exits
            return false;
        }
        if(vis[node]){
            return true;
        }
        vis[node]=true;
        path.insert(node);
        bool res=true;
        for(auto &it:edges.at(node)){
            res&=dfs(it,edges,vis,path);
        }
        auto it=path.find(node);
        if(it!=path.end())
            path.erase(it);
        return res;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<bool> visited(numCourses,false);
        unordered_map<int,vector<int>> edges;
        for(auto &it:prerequisites){
            edges[it[0]].push_back(it[1]);
        }
        unordered_set<int> path;
        for(auto &it:edges){
            if(!dfs(it.first,edges,visited,path)){
                return false;
            }
        }
        return true;
    }
};


int main(){

}

//best
class Solution {
public:
    bool dfs(int node, vector<int> adjl[], vector<int> &vis, vector<int> &pathvis){
        vis[node]=1;
        pathvis[node]=1;

        for(auto it:adjl[node]){
            if(!vis[it]){
                if(dfs(it,adjl,vis,pathvis)==true) return true;
            }
            else if(pathvis[it]) return true;
        }

        pathvis[node]=0;
        return false;

    }

    bool canFinish(int n, vector<vector<int>>& pre) {
        vector<int> vis(n,0);
        vector<int> pathvis(n,0);
        vector<int> adjl[n];
        for(int i=0;i<pre.size();i++){
            adjl[pre[i][0]].push_back(pre[i][1]);
        }
        for(int i=0;i<n;i++){
            if(!vis[i]){
                if(dfs(i,adjl,vis,pathvis)==true) return false;
            }
        }
        return true;
    }
};