#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    // Hierholzer using stack -- special algo
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string,priority_queue<string,vector<string>,greater<string>>> adj;
        for(auto &it:tickets){
            adj[it[0]].push(it[1]);
        }
        stack<string> st;
        st.push("JFK");
        vector<string> path;
        while(!st.empty()){
            string u=st.top();
            if(!adj[u].empty()){
                string v=adj[u].top();
                adj[u].pop();
                st.push(v);
            }else{
                path.push_back(u);
                st.pop();
            }
            
        }
        reverse(path.begin(),path.end());
        return path;
    }
};

//another one is with special dfs 
/*
Step 2: Apply Euler Path Conditions

For directed graph:

👉 Euler path exists if:

One node: out = in + 1 → start
One node: in = out + 1 → end
Others: in = out

        vector<vector<int>> adj(n + 1);
        vector<int> indegree(n + 1, 0), outdegree(n + 1, 0);

        // Build graph
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            outdegree[u]++;
            indegree[v]++;
        }

        // Find start node
        int start = 1;
        for (int i = 1; i <= n; i++) {
            if (outdegree[i] == indegree[i] + 1) {
                start = i; // Euler path start
                break;
            }
            if (outdegree[i] > 0) {
                start = i; // fallback (circuit case)
            }
        }

        dfs(start, adj);
*/
void dfs(int u, vector<vector<int>>& adj) {
        while (!adj[u].empty()) {
            int v = adj[u].back();
            adj[u].pop_back();   // remove edge
            dfs(v, adj);
        }
        path.push_back(u); // add when stuck (backtracking)
}
int main(){
    int n;
    cin>>n;
    vector<vector<string>> inp(n,vector<string>(2));
    for(auto &it:inp){
        cin>>it[0]>>it[1];
    }
    Solution s;
    auto res=s.findItinerary(inp);
    for(auto &it:res){
        cout<<it<<" ";
    }
}

//best
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& v) {
      int n=v.size();
      map<string,multiset<string>>adj;
      int i;
      for(i=0;i<v.size();i++)
      {
        adj[v[i][0]].insert(v[i][1]);
      }  

      stack<string>st;
      st.push("JFK");
      vector<string>ans;
      while(!st.empty())
      {
        auto e=st.top();
        if(adj[e].size()==0)
        {
            ans.push_back(e);
            st.pop();
        }
        else
        {
           auto it=adj[e].begin();
           string s=*it;
           adj[e].erase(it);
           st.push(s);   
        }
      }
      reverse(ans.begin(),ans.end());
      return ans;
    }
};

//another ok one
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, vector<string>> mp;
        int count = 0;
        for (auto &t : tickets) {
            mp[t[0]].push_back(t[1]);
        }
        for (auto &[_, arr] : mp) {
            sort(arr.begin(), arr.end(), greater<>());
        }
        vector<string> res;
        auto dfs = [&] (this auto &&dfs, string& cur) -> void {
            while (!mp[cur].empty()) {
                auto next = mp[cur].back();
                mp[cur].pop_back();
                dfs(next);
            }
            res.push_back(cur);
        };
        string start = "JFK";
        dfs(start);
        reverse(res.begin(), res.end());
        return res;
    }
};
//ways of functor
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, vector<string>> graph;
        
        for (auto& ticket : tickets) {
            graph[ticket[0]].push_back(ticket[1]);
        }
        
        for (auto& [_, destinations] : graph) {
            sort(destinations.rbegin(), destinations.rend());
        }
        
        vector<string> itinerary;
        
        function<void(const string&)> dfs = [&](const string& airport) {
            while (!graph[airport].empty()) {
                string next = graph[airport].back();
                graph[airport].pop_back();
                dfs(next);
            }
            itinerary.push_back(airport);
        };
        
        dfs("JFK");
        reverse(itinerary.begin(), itinerary.end());
        
        return itinerary;
    }
};
