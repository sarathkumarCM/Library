#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        if(times.size()<n-1){
            return -1; //not enough edges atleast n-1 edges are needed else 2 connected components
        }
        unordered_set<int> vis;
        vector<int> dist(n+1,-1);
        dist[0]=0; //since it aint considered
        //make adj list
        unordered_map<int,vector<pair<int,int>>> adj;
        for(auto &it: times){
            adj[it[0]].push_back({it[1],it[2]});
        }
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> minH;
        //vis.insert(k);
        dist[k]=0;
        minH.push({0,k});

        while(!minH.empty()){
            pair<int,int> top=minH.top();
            minH.pop();
            if(vis.find(top.second)!=vis.end()){
                continue;
            }
            vis.insert(top.second);
            dist[top.second]=top.first;
            for(auto &it:adj[top.second]){
                if(vis.find(it.first)==vis.end()){
                    minH.push({it.second+top.first,it.first});
                }
            }
        }
        if(*min_element(dist.begin(),dist.end())==-1){
            return -1;
        }
        return *max_element(dist.begin(),dist.end());

    }
};

int main(){
    int n;
    cin>>n;
    vector<vector<int>> inp(n,vector<int>(3));
    for(auto &it:inp){
        cin>>it[0]>>it[1]>>it[2];
    }

    int nodes,start;
    cin>>nodes>>start;
    Solution s;
    cout<<s.networkDelayTime(inp,nodes,start);
}

//best
class Solution {
    // Fixed size based on constraints: N=100, E=6000
    int head[101], nxt[6001], to[6001], weight[6001];
    int edge_count;

    void add_edge(int u, int v, int w) {
        to[edge_count] = v;
        weight[edge_count] = w;
        nxt[edge_count] = head[u];
        head[u] = edge_count++;
    }

public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Reset static arrays
        edge_count = 0;
        fill(head, head + n + 1, -1);
        
        for (const auto& t : times) {
            add_edge(t[0], t[1], t[2]);
        }

        vector<int> dist(n + 1, 1e9);
        vector<bool> in_queue(n + 1, false);
        queue<int> q;

        dist[k] = 0;
        q.push(k);
        in_queue[k] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in_queue[u] = false;

            for (int i = head[u]; i != -1; i = nxt[i]) {
                int v = to[i];
                int w = weight[i];
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    if (!in_queue[v]) {
                        q.push(v);
                        in_queue[v] = true;
                    }
                }
            }
        }

        int res = 0;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == 1e9) return -1;
            res = max(res, dist[i]);
        }
        return res;
    }
};

//better than mine
class Solution {
public:

    vector<int> dijkstra(int src, vector<vector<pair<int,int>>>& adj){
        int V = adj.size();
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0, src}); // dist, src

        while(!pq.empty()){
            int currentDist = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if(currentDist > dist[u]){continue;}
            for(auto [v,w] : adj[u]){
                int newDist = dist[u] + w;
                if(newDist < dist[v]){
                    dist[v] = newDist;
                    pq.push({newDist, v});
                }
            }
        }
        return dist;
    }
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int,int>>> adj(n+1); // u-> v,w
        for(auto &i: times){
            adj[i[0]].push_back({i[1], i[2]});
        }

        vector<int> dist = dijkstra(k, adj);
        int ans=0;
        for(int i=1;i<=n;i++){
            if(dist[i]==INT_MAX){
                return -1;
            }
            ans = max(ans, dist[i]);
        }
        return ans;
    }
};

//easier better than mine
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> adj(n+1);
        vector<int> dist(n+1, INT_MAX);

        for(auto &it : times){
            adj[it[0]].push_back({it[1],it[2]});
        }

        priority_queue<pair<int, int> , vector<pair<int, int>> , greater<pair<int, int>>> q;
        q.push({0 , k});
        dist[k] = 0;

        while(!q.empty()){
            auto [time , node] = q.top();
            q.pop();

            for(auto it : adj[node]){
                int neighbour = it.first;
                int time1 = it.second;

                if(time1 + time < dist[neighbour]){
                    dist[neighbour] = time + time1;
                    q.push({time1+time , neighbour});
                }
            }
        }

        int maxi = 0;
        for(int i=1; i<=n; i++){
            if(dist[i] == INT_MAX) return -1;
            else maxi = max(maxi , dist[i]);
        }

        return maxi;
    }
};