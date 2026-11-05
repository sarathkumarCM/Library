#include<bits/stdc++.h>

using namespace std;

class Solution {
public:

    int bfs(string beg,string en,unordered_map<string,vector<string>>  &adj){
        if(beg==en){
            return 1;
        } // can be removed
        unordered_set<string> vis;
        queue<string> q;
        q.push(beg);
        int cnt=0;
        while(!q.empty()){
            int len=q.size();
            while(len>0){
                string  cur=q.front();
                vis.insert(cur);
                q.pop();
                if(en==cur){
                    return cnt+1;
                }
                for(auto &it:adj[cur]){
                    if(vis.find(it)==vis.end()){
                        q.push(it);
                    }
                }
                len--;
            }
            cnt++;
        }

        return 0;
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        wordList.push_back(beginWord);
        unordered_map<string,vector<string>> adj;

        for(int i=0;i<wordList.size();i++){
            string curWord=wordList[i];
            for(int j=i+1;j<wordList.size();j++){
                int diff=0;
                for(int k=0;k<curWord.size();k++){
                    if(curWord[k]!=wordList[j][k]){
                        diff++;
                    }
                    if(diff>1){
                        break;
                    }
                }
                if(diff==1){
                    adj[curWord].push_back(wordList[j]);
                    adj[wordList[j]].push_back(curWord);
                }
            }
        }
        for(auto &it:adj){
            cerr<<" Adj of "<<it.first<<" :";
            for(auto &it2:it.second){
                cerr<<" "<<it2;
            }
            cerr<<endl;
        }

        int res=bfs(beginWord,endWord,adj);
        return res;
    }
};

int main(){
    int n;
    cin>>n;
    string b,e;
    cin>>b>>e;
    vector<string> wl(n);
    for(auto &it:wl){
        cin>>it;
    }
    Solution s;
    cout<<s.ladderLength(b,e,wl);

}


//best

using u64 = unsigned long long;
const int CHAR = 5;
const int C = 26;
const int INF = 0x3f3f3f3f;

class Solution {
private:
    int n, str_len;
    vector<u64> hash_values;
    unordered_map<u64, int> lookup_gid;  // hash value -> graph id
    vector<int> df, db;

    u64 hash(string& s) {
        u64 h = 0;
        for (auto& _c : s) {
            u64 c = _c - 'a' + 1;
            h = (h << CHAR) | c;
        }
        return h;
    }

    void add_hash(int i, string& s) {
        hash_values[i] = hash(s);
        lookup_gid[hash_values[i]] = i;
    }

public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int beginNode = -1, endNode = -1;

        n = (int)wordList.size();
        str_len = (int)beginWord.size();
        hash_values.resize(n + 1);
        lookup_gid.clear();

        u64 hbegin = hash(beginWord);
        u64 hend = hash(endWord);
        for (int i = 0; i < n; i++) {
            add_hash(i, wordList[i]);
            if (hash_values[i] == hend) {
                endNode = i;
            } else if (hash_values[i] == hbegin) {
                beginNode = i;
            }
        }

        if (endNode == -1) return 0;
        if (beginNode == -1) {
            add_hash(n, beginWord);
            beginNode = n;
            n++;
        }

        queue<int> qf, qb;  // frontward, backward
        df.assign(n + 1, INF);
        db.assign(n + 1, INF);
        df[beginNode] = 1; qf.push(beginNode);
        db[endNode] = 1;   qb.push(endNode);


        auto expand = [&](queue<int>& q, vector<int>& d_cur, vector<int>& d_other) {
            int ans = INF;
            int qsz = (int)q.size();

            while (qsz--) {
                int u = q.front(); q.pop();
                u64 hu = hash_values[u];

                // enumerate all possible neighbors
                for (int i = 0; i < str_len; i++) {
                    // L [i-th block] R
                    u64 step = 1ULL << (CHAR * i);

                    u64 L = hu >> (CHAR * (i + 1)) << (CHAR * (i + 1));
                    u64 R = hu & (step - 1);

                    
                    for (u64 M = step; M <= step * C; M += step) {
                        u64 hv = L | M | R;
                        if (hv == hu) continue;
                        auto it = lookup_gid.find(hv);
                        if (it == lookup_gid.end()) continue;
                        
                        int v = it->second;
                        
                        if (d_cur[v] == INF) {
                            d_cur[v] = d_cur[u] + 1;
                            q.push(v);
                        }

                        ans = min(ans, d_cur[v] + d_other[v] - 1);
                    }
                }
            }

            return ans;
        };

        while (!qf.empty() && !qb.empty()) {
            int ans = INF;
            if (qf.size() < qb.size()) ans = expand(qf, df, db);
            else                       ans = expand(qb, db, df);
            if (ans != INF) return ans;
        }

        return 0;
    }
};  


//bidirectional bfs
#include <bits/stdc++.h>
using namespace std;

int bidirectionalBFS(int n, vector<vector<int>>& adj, int src, int target) {
    if (src == target) return 0;

    vector<int> dist1(n, -1), dist2(n, -1);
    queue<int> q1, q2;

    q1.push(src);
    q2.push(target);

    dist1[src] = 0;
    dist2[target] = 0;

    while (!q1.empty() && !q2.empty()) {

        // Always expand smaller queue
        if (q1.size() <= q2.size()) {
            int size = q1.size();
            while (size--) {
                int u = q1.front(); q1.pop();

                for (int v : adj[u]) {
                    if (dist1[v] == -1) {
                        dist1[v] = dist1[u] + 1;
                        q1.push(v);

                        // 🎯 Meet condition
                        if (dist2[v] != -1) {
                            return dist1[v] + dist2[v];
                        }
                    }
                }
            }
        } else {
            int size = q2.size();
            while (size--) {
                int u = q2.front(); q2.pop();

                for (int v : adj[u]) {
                    if (dist2[v] == -1) {
                        dist2[v] = dist2[u] + 1;
                        q2.push(v);

                        // 🎯 Meet condition
                        if (dist1[v] != -1) {
                            return dist1[v] + dist2[v];
                        }
                    }
                }
            }
        }
    }

    return -1; // no path
}