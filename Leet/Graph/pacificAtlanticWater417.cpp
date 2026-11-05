#include<bits/stdc++.h>

using namespace std;

class Solution {
public:

    vector<pair<int,int>> dirs={{1,0},{0,1},{-1,0},{0,-1}};
    void bfs(int r, int c, int m,int n,vector<vector<int>>& heights,vector<vector<bool>>& visited, vector<vector<int>> &ans){
        if((r==0&&c==n-1) || (r==m-1 && c==0)){
            visited[r][c]=true;
            ans.push_back({r,c});
            return;
        }
        queue<pair<int,int>> q;
        vector<vector<bool>> vis(m,vector<bool>(n,false));
        q.push({r,c});
        vis[r][c]=true;
        bool atl=false,pac=false;
        if(c==0||r==0){
            pac=true;
        }
        if(r==(m-1) || c==(n-1)){
            atl=true;
        }
        while(!q.empty()){
            int len=q.size();
            while(len>0){
                auto [x,y]=q.front();
                q.pop();
                for(auto &it:dirs){
                    int dx=x+it.first,dy=y+it.second;
                    if(min(dx,dy)<0 || dx>=m ||dy>=n || vis[dx][dy] || heights[dx][dy]>heights[x][y]){
                        continue;
                    }
                    if(visited[dx][dy]){
                        visited[r][c]=true;
                        ans.push_back({r,c});
                        return;
                    }
                    if(dx==0 || dy ==0){
                        pac=true;
                    }
                    if(dx==(m-1) || dy==(n-1)){
                        atl=true;
                    }
                    q.push({dx,dy});
                    vis[dx][dy]=true;
                }
                if(pac&&atl){
                    visited[r][c]=true;
                    ans.push_back({r,c});
                    return;
                }
                len--;
            }
        }
        if(pac==true && atl==true){
            visited[r][c]=true;
            ans.push_back({r,c});
        }
    }
    vector<vector<int>> pacificAtlantic2(vector<vector<int>>& heights) {
        int m=heights.size();
        int n=heights[0].size();
        vector<vector<bool>> visited(m,vector<bool>(n,false));
        vector<vector<int>> ans;

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                bfs(i,j,m,n,heights,visited,ans);
            }
        }
        return ans;
        
    }
    void dfs(int i,int j, int m, int n, vector<vector<int>> &grid, vector<vector<bool>> &visited){
        visited[i][j]=true;
        for(auto &it:dirs){
            int dx=i+it.first,dy=j+it.second;
            if(min(dx,dy)<0 || dx>=m ||dy>=n || visited[dx][dy] || grid[dx][dy]<grid[i][j]){
                continue;
            }
            dfs(dx,dy,m,n,grid,visited);
        }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m=heights.size();
        int n=heights[0].size();
        vector<vector<bool>> pacific(m,vector<bool>(n,false));
        vector<vector<bool>> atlantic(m,vector<bool>(n,false));
        vector<vector<int>> ans;

        
        for(int i=0;i<m;i++){
            dfs(i,0,m,n,heights,pacific);
            dfs(i,n-1,m,n,heights,atlantic);
        }
        for(int i=0;i<n;i++){
            dfs(0,i,m,n,heights,pacific);
            dfs(m-1,i,m,n,heights,atlantic);
        }
        
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(atlantic[i][j]&&pacific[i][j]){
                    ans.push_back({i,j});
                }
            }
        }
        return ans;
        
    }
};

int main(){

    int m,n;
    cin>> m>>n;
    vector<vector<int>> grid(m,vector<int>(n));
    for(auto &it:grid){
        for(auto &it2: it){
            cin>>it2;
        }
    }
    Solution s;
    auto res=s.pacificAtlantic(grid);
    for(auto &it:res){
        for(auto &it2:it){
            cout<<it2<<" ";
        }
        cout<<endl;
    }

}

//diff
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        vector<vector<int>> water_Atlantic(n,vector<int>(m,0));
        vector<vector<int>> water_Pacific(n,vector<int>(m,0));
        queue<pair<int,int>> Atlantic;
        queue<pair<int,int>> Pacific;
        int check[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
        vector<vector<int>> ans;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(i==0 || j==0)
                    Pacific.push({i,j});
                if(i==n-1 || j==m-1)
                    Atlantic.push({i,j});
            }
        }

        while(!Atlantic.empty()){
            auto [a,b]=Atlantic.front();
            Atlantic.pop();
            if(water_Atlantic[a][b])
                continue;
            water_Atlantic[a][b]=1;
            for(auto & it:check){
                int i = a+it[0];
                int j = b+it[1];
                if(i<0 || j<0 || i>n-1 || j>m-1)
                    continue;
                if(water_Atlantic[i][j])
                    continue;
                if(heights[i][j]>=heights[a][b])
                    Atlantic.push({i,j});
            }
        }
        while(!Pacific.empty()){
            auto [a,b]=Pacific.front();
            Pacific.pop();
            if(water_Pacific[a][b])
                continue;
            water_Pacific[a][b]=1;
            for(auto & it:check){
                int i = a+it[0];
                int j = b+it[1];
                if(i<0 || j<0 || i>n-1 || j>m-1)
                    continue;
                if(water_Pacific[i][j])
                    continue;
                if(heights[i][j]>=heights[a][b])
                    Pacific.push({i,j});
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(water_Pacific[i][j]==1 && water_Atlantic[i][j]==1)
                ans.push_back({i,j});
            }
        }
        return ans;
    }
};

