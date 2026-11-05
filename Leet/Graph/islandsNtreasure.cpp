#include<bits/stdc++.h>
using namespace std;

static int INF=2147483647;

class Solution {
public:
    
    vector<pair<int,int>> dirs={{1,0},{-1,0},{0,1},{0,-1}};
    int bfs2(int r, int c, int m, int n,vector<vector<int>> &grid){
        unordered_set<int> vis;
        vector<int> dist(n);
        queue<pair<int,int>> q;
        q.push(make_pair(r,c));
        visited.insert(make_pair(r,c));
        int length=0;
        while(!q.empty()){
            int len=q.size();
            while(len>0){
                pair<int,int> f=q.front();
                q.pop();
                if(grid[f.first][f.second]==0){
                    return length;
                }
                r=f.first,c=f.second;
                for(auto &it:dirs){
                    if(min(r+it.first,c+it.second)<0 || r+it.first>=m || c+it.second>=n || visited.find(make_pair(r+it.first,c+it.second))!=visited.end() || grid[r+it.first][c+it.second]==-1)
                        continue;
                    q.push(make_pair(r+it.first,c+it.second));
                    visited.insert(make_pair(r+it.first,c+it.second));
                }
                len--;
            }
            length++;
        }
        return length;
    }
    void islandsAndTreasure(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==INF){
                    grid[i][j]=bfs2(i,j,m,n,grid);
                }
            }
        }
    }

    
};

int main(){

    int r,c;
    cin>>r>>c;
    vector<vector<int>> grid(r,vector<int>(c));
    //char ch;
    for(auto &it:grid){
        for(auto &it2:it){
            cin>>it2;
        }
    }
    // for(auto &it:grid){
    //     cerr<<endl;
    //     for(auto &it2:it){
    //         cerr<<it2<<" ";
    //     }
    // }
    Solution s;
    s.islandsAndTreasure(grid);
    for(auto &it:grid){
        
        for(auto &it2:it){
            cout<<it2<<" ";
        }
        cout<<endl;
    }
}

// Best
class Solution {
public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
        int r=grid.size();
        int c=grid[0].size();
        queue<pair<int,int>>q;

        int INF=2147483647;

        for(int i=0; i<r; i++){
            for(int j=0; j<c; j++){
                if(grid[i][j]==0){
                    q.push({i,j});
                }
            }
        }

        vector<pair<int,int>>dir={{-1,0},{0,-1},{1,0},{0,1}};

        while(!q.empty()){
            auto [x,y]=q.front();
            q.pop();

            for(auto it:dir){
                int X=x+it.first;
                int Y=y+it.second;

                if(X>=0 && Y>=0 && X<r && Y<c && grid[X][Y]==INF){
                    grid[X][Y]=grid[x][y]+1;
                    q.push({X,Y});
                }
            }
        }
    }
};