#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool dfs(int node, unordered_map<int,vector<int>> &edges, vector<bool> &vis,unordered_set<int> &path, vector<int> &topOrder){
        if(path.find(node)!=path.end()){ // cycle exits
            return false;
        }
        if(vis[node]){
            return true;
        }
        vis[node]=true;
        path.insert(node);
        bool res=true;
        for(auto &it:edges[node]    ){
            res&=dfs(it,edges,vis,path,topOrder);
        }
        auto it=path.find(node);
        if(it!=path.end())
            path.erase(it);
        topOrder.push_back(node);
        return res;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<bool> visited(numCourses,false);
        unordered_map<int,vector<int>> edges;
        for(int i=0;i<numCourses;i++){
            edges[i]={};
        }
        for(auto &it:prerequisites){
            edges[it[0]].push_back(it[1]);
        }
        unordered_set<int> path;
        vector<int> topOrder;
        for(auto &it:edges){
            if(!dfs(it.first,edges,visited,path, topOrder)){
                return {};
            }
        }
        return topOrder;
    }
};

//best read kahns algo
class Solution {
public:
    void dfs(int node,vector<int>&ans,vector<vector<int>>&a,vector<int>&v){
        ans.push_back(node);
        v[node] = -1;
        for(int i = 0 ; i < a[node].size() ; i++){
            if(--v[a[node][i]] == 0){
                dfs(a[node][i], ans, a, v);
            }
        }
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int>v(numCourses);
        vector<vector<int>>m(numCourses);
        vector<int>ans;
        for(int i = 0 ; i < prerequisites.size() ; i++){
            m[prerequisites[i][1]].push_back(prerequisites[i][0]);
            v[prerequisites[i][0]]++;
        }
        for(int i = 0 ; i < numCourses ; i++){
            if(v[i] == 0)
                dfs(i,ans,m,v);
        }
        if(ans.size() == numCourses)
            return ans;
        return {};
    }
};

//ok
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);

        for (auto& p : prerequisites) {
            int a = p[0];
            int b = p[1];
            graph[b].push_back(a);
            indegree[a]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> order;

        while (!q.empty()) {
            int course = q.front();
            q.pop();
            order.push_back(course);

            for (int next : graph[course]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        if (order.size() == numCourses) {
            return order;
        }

        return {};
    }
};