#include<bits/stdc++.h>

using namespace std;
class Solution {
    public:
        bool canVisitAllRooms(vector<vector<int>>& rooms) {
            int sz=rooms.size();
            vector<bool> visited(sz,false);
            queue<int> q;
            q.push(0);
            while(!q.empty()){
                int toGo=q.front();
                q.pop();
                if(!visited[toGo]){
                    for(auto &it: rooms[toGo]){
                        if(!visited[it]){
                            q.push(it);
                        }
                    }
                }
                visited[toGo]=true;

            }
            for(auto it:visited){
                if(it==false)
                    return false;
            }
            return true;
        }
    };


int main(){
    vector<vector<int>> rooms={{1},{2},{3},{}};

    Solution s;
    bool ans=s.canVisitAllRooms(rooms);
    cout<<ans<<endl;
}

// recursion
void dfs(int node,vector<int>& visit,vector<vector<int>>& g){
    visit[node] = 1;
    for(auto x:g[node]){
        if(!visit[x]){
            dfs(x,visit,g);
        }
    }
    return;
}