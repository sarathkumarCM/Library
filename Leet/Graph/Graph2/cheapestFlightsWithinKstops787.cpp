#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        if(src==dst) return 0;
        unordered_map<int,vector<pair<int,int>>> adj;
        for(auto &it:flights){
            adj[it[0]].push_back({it[1],it[2]}); // u,{v,weight}
        }
        vector<int> dist(n,1e9);
        dist[src]=0;
        for(int i=0;i<=k;i++){
            vector<int> tmpDist=dist;
            for(auto &it: flights){
                int u=it[0];
                int v=it[1];
                int weight=it[2];
                if(dist[u]+weight<tmpDist[v]){
                    tmpDist[v]=dist[u]+weight;
                }
            }
            dist=tmpDist;
        }
        return dist[dst]==1e9?-1:dist[dst];

    }
};

int main(){
    int n,m;
    cin>>m>>n;
    vector<vector<int>> fl(n,vector<int>(3));
    for(auto &it:fl){
        cin>>it[0]>>it[1]>>it[2];
    }
    int src,dst,k;
    cin>>src>>dst>>k;
    Solution s;
    cout<<s.findCheapestPrice(m,fl,src,dst,k);

}


//SPFA
class Solution2 {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<int> prices(n, INT_MAX);
        prices[src] = 0;
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& flight : flights) {
            adj[flight[0]].emplace_back(flight[1], flight[2]);
        }

        queue<tuple<int, int, int>> q;
        q.push({0, src, 0});

        while (!q.empty()) {
            auto [cst, node, stops] = q.front();
            q.pop();
            if (stops > k) continue;

            for (const auto& neighbor : adj[node]) {
                int nei = neighbor.first, w = neighbor.second;
                int nextCost = cst + w;
                if (nextCost < prices[nei]) {
                    prices[nei] = nextCost;
                    q.push({nextCost, nei, stops + 1});
                }
            }
        }
        return prices[dst] == INT_MAX ? -1 : prices[dst];
    }
};

//another
class Solution3 {
public:
    int findCheapestPrice(int n, vector<vector<int>>& f, int src, int dst, int k) {
        vector<vector<pair<int,int>>> adj(n);
        for(int i=0;i<f.size();i++){
            int fr = f[i][0];
            int to = f[i][1];
            int p = f[i][2];
            adj[fr].push_back({to,p});
        }
        queue<pair<int,int>> pq;
        pq.push({0,src});
        vector<int> dist(n,1e9);
        dist[src]=0;
        int st =0;
        while(!pq.empty() && st<=k){
            int sz = pq.size();
            while(sz--){
                pair<int,int> z = pq.front();
                pq.pop();
                int pr = z.first;
                int nod = z.second;
                for(auto it:adj[nod]){
                    int npr = it.second+pr;
                    if(npr<dist[it.first]){
                        dist[it.first]=npr;
                        pq.push({npr,it.first});
                    }
                }
            }
            st++;
        }
        return dist[dst]==1e9 ? -1 : dist[dst];
    }
};

//Dijikstra
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        int INF = 1e9;
        vector<vector<pair<int, int>>> adj(n);
        vector<vector<int>> dist(n, vector<int>(k + 5, INF));

        for (auto& flight : flights) {
            adj[flight[0]].emplace_back(flight[1], flight[2]);
        }

        dist[src][0] = 0;
        priority_queue<tuple<int, int, int>,
                       vector<tuple<int, int, int>>, greater<>> minHeap;
        minHeap.emplace(0, src, -1);

        while (!minHeap.empty()) {
            auto [cst, node, stops] = minHeap.top();
            minHeap.pop();
            if (node == dst) return cst;
            if (stops == k || dist[node][stops + 1] < cst) continue;
            for (auto& [nei, w] : adj[node]) {
                int nextCst = cst + w;
                int nextStops = stops + 1;
                if (dist[nei][nextStops + 1] > nextCst) {
                    dist[nei][nextStops + 1] = nextCst;
                    minHeap.emplace(nextCst, nei, nextStops);
                }
            }
        }
        return -1;
    }
};