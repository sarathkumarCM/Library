#include<bits/stdc++.h>

using namespace std;

class Solution {
public:

    vector<pair<int,int>> dirs={{0,1},{1,0},{-1,0},{0,-1}};

    void dfs(int r, int c, int m, int n, vector<vector<char>>& board,vector<vector<bool>> &visited){
        if(visited[r][c]){
           return;
        }
        if(board[r][c]=='X'){
            return;
        }
        visited[r][c]=true;
        for(auto &it:dirs){
            int dr=r+it.first,dc=c+it.second;
            if(min(dr,dc)<0|| dr>m-1 ||dc>n-1 || visited[dr][dc] || board[dr][dc]=='X'){
                continue;
            }

            dfs(dr,dc,m,n,board,visited);
        
        }
        return;
    }
    void solve(vector<vector<char>>& board) {
        int m=board.size();
        int n=board[0].size();
        queue<pair<int,int>> q;
        for(int i=0;i<m;i++){
            if(board[i][0]=='O'){
                q.push({i,0});
            }
            if(board[i][n-1]=='O'){
                q.push({i,n-1});
            }
        }
        for(int i=0;i<n;i++){
            if(board[0][i]=='O'){
                q.push({0,i});
            }
            if(board[m-1][i]=='O'){
                q.push({m-1,i});
            }
        }

        vector<vector<bool>> visited(m,vector<bool>(n,false));
        while(!q.empty()){
            auto [x,y]=q.front();
            q.pop();
            dfs(x,y,m,n,board,visited);
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if((!visited[i][j])&& board[i][j]=='O'){
                    board[i][j]='X';
                }
            }
        }
    }
};

int main(){

    int m,n;
    cin>> m>>n;
    vector<vector<char>> grid(m,vector<char>(n));
    for(auto &it:grid){
        for(auto &it2: it){
            cin>>it2;
        }
    }
    Solution s;
    s.solve(grid);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }

}
