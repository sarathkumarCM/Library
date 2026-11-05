#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int manDist(const pair<int,int> &pt1,const pair<int,int> &pt2){
        return abs(pt1.first-pt2.first)+abs(pt1.second-pt2.second);
    }
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n=points.size();
        unordered_map<int,vector<pair<int,int>>> adj;
        for(int i=0;i<n-1;i++){
            for(int j=i+1;j<n;j++){
                int dist=manDist({points[i][0],points[i][1]},{points[j][0],points[j][1]});
                adj[i].push_back({dist,j});
                adj[j].push_back({dist,i});
            }
        }
        //start node =0;
        unordered_map<int,bool> vis;
        vector<pair<int,int>> ed;
        priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> minH;
        for(auto &it:adj[0]){
            minH.push({it.first,{0,it.second}});
        }
        vis[0]=true;
        int cost=0;
        while(ed.size()<=n && !minH.empty()){
            auto [weight, edge]=minH.top();
            minH.pop();
            if(vis[edge.second]) continue;
            vis[edge.second]=true;
            cost+=weight;
            ed.push_back(edge);
            for(auto &it:adj[edge.second]){
                if(vis[it.second]) continue;
                minH.push({it.first,{edge.second,it.second}});
            }
        }
        return cost;
    }
};

int main(){
    int n;
    cin>>n;
    vector<vector<int>> inp(n,vector<int>(2));
    for(auto &it:inp){
        cin>>it[0]>>it[1];
    }
    Solution s;
    cout<<s.minCostConnectPoints(inp);
}

//best -understand
class Solution2 {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        if (points.size() < 1) return 0;
        auto dist = [](int x1, int y1, int x2, int y2) {
            return abs (x1-x2) + abs(y1-y2);
        };
        
        unsigned sz = points.size();
        vector<int> minDists(sz,0);
		//Initialize
        int result = 0;
        minDists[0] = INT_MAX;
        for (auto i = 1 ; i < sz; i++) {
            minDists[i] = dist(points[0][0],points[0][1],points[i][0],points[i][1]);
        }
		
		//Build Spanning Tree
        for (auto i = 1; i < sz; i++) {
            auto it = min_element(minDists.begin(), minDists.end());
            result += *it;
            int index = it - minDists.begin(); //finds the index of the min element
            *it = INT_MAX;
            for (auto i = 0 ; i < sz; i++) {
                if (minDists[i] == INT_MAX) continue;
                minDists[i] = min(minDists[i], dist(points[i][0], points[i][1], points[index][0], points[index][1]));
            }
        }
        return result;        
    }
};

//Best overall
class Solution {
    struct DSU {
        int n;
        vector<int> p, r;
        DSU(int n = 0) : n(n), p(n), r(n, 0) { iota(p.begin(), p.end(), 0); }
        int find(int a) { return p[a] == a ? a : p[a] = find(p[a]); }
        bool unite(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b)
                return false;
            if (r[a] < r[b])
                swap(a, b);
            p[b] = a;
            if (r[a] == r[b])
                r[a]++;
            return true;
        }
    };

    struct Pt {
        int x, y, id;
    };

    int manh(const Pt& a, const Pt& b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }

    struct BIT {
        int n;
        vector<pair<int, int>> bit; // (value, index)
        BIT(int n = 0) : n(n), bit(n + 1, {INT_MAX, -1}) {}
        static pair<int, int> better(pair<int, int> a, pair<int, int> b) {
            if (a.first < b.first)
                return a;
            return b;
        }
        void update(int i, pair<int, int> val) {
            for (; i <= n; i += i & -i)
                bit[i] = better(bit[i], val);
        }
        pair<int, int> query(int i) {
            pair<int, int> res = {INT_MAX, -1};
            for (; i > 0; i -= i & -i)
                res = better(res, bit[i]);
            return res;
        }
        void reset() {
            fill(bit.begin(), bit.end(), pair<int, int>{INT_MAX, -1});
        }
    };

public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<Pt> pts(n);
        for (int i = 0; i < n; i++) {
            pts[i].x = points[i][0];
            pts[i].y = points[i][1];
            pts[i].id = i;
        }

        vector<tuple<int, int, int>> edges; // (w,u,v)

        for (int t = 0; t < 4; t++) {
            // build transformed points for this sweep (keep original structure)
            vector<Pt> trans(n);
            for (int i = 0; i < n; i++) {
                int x = points[i][0], y = points[i][1];
                int tx = x, ty = y;
                if (t == 0) {
                    tx = x;
                    ty = y;
                } else if (t == 1) {
                    tx = y;
                    ty = x;
                } else if (t == 2) {
                    tx = -x;
                    ty = y;
                } else {
                    tx = -y;
                    ty = x;
                }
                trans[i] = {tx, ty, i};
            }
            // sort by x then y
            sort(trans.begin(), trans.end(), [](const Pt& a, const Pt& b) {
                if (a.x != b.x)
                    return a.x < b.x;
                return a.y < b.y;
            });

            // coordinate compress keys = y - x
            vector<int> keys(n);
            for (int i = 0; i < n; i++)
                keys[i] = trans[i].y - trans[i].x;
            vector<int> comp = keys;
            sort(comp.begin(), comp.end());
            comp.erase(unique(comp.begin(), comp.end()), comp.end());
            int m = comp.size();
            BIT bit(m);

            // sweep from right to left; query among keys >= current key
            for (int i = n - 1; i >= 0; i--) {
                int key = trans[i].y - trans[i].x;
                int idx0 = int(lower_bound(comp.begin(), comp.end(), key) -
                               comp.begin()) +
                           1; // 1-based
                int idx = m - idx0 +
                          1; // reverse to make prefix BIT query act as suffix
                auto q = bit.query(idx);
                if (q.second != -1) {
                    int j = q.second;
                    int u = trans[i].id;
                    int v = trans[j].id;
                    edges.emplace_back(manh(trans[i], trans[j]), u, v);
                }
                pair<int, int> val = {trans[i].x + trans[i].y, i};
                bit.update(idx, val);
            }
        }

        // run Kruskal on candidate edges
        sort(edges.begin(), edges.end());
        DSU dsu(n);
        long long res = 0;
        for (auto& e : edges) {
            int w, u, v;
            tie(w, u, v) = e;
            if (dsu.unite(u, v))
                res += w;
        }
        return (int)res;
    }
};