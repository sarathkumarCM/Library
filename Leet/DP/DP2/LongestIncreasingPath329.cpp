#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int M,N;
    /* not working
    vector<pair<int,int>> dirs={{0,1},{1,0},{-1,0},{0,-1}};
    void bfs(int i,int j, vector<vector<bool>> &vis, vector<vector<int>>& matrix, vector<vector<int>>& dp){
        int m=matrix.size(),n=matrix[0].size();
        queue<pair<int,int>> q;
        q.push({i,j});
        dp[i][j]=1;
        //cerr<<"Beg: "<<i<<" ,"<<j<<endl;
        while(!q.empty()){
            int sz=q.size();
            while(sz>0){
                auto [r,c]=q.front();
                q.pop();
                //cerr<<"I am At: "<<r<<" "<<c<<endl;
                for(auto &it:dirs){
                    int dr=r+it.first,dc=c+it.second;
                    if(min(dr,dc)<0 || dr>=m || dc>=n) continue;
                    if(matrix[dr][dc]<=matrix[r][c]) continue;
                    if(vis[dr][dc]){ // special dp case
                        dp[dr][dc]=max(dp[dr][dc],dp[r][c]+1);
                        q.push({dr,dc});
                        //cerr<<"\t\tVis: DP["<<dr<<"]["<<dc<<"]: "<<dp[dr][dc]<<endl;
                        continue;
                    }
                    q.push({dr,dc});
                    vis[dr][dc]=true;
                    dp[dr][dc]=dp[r][c]+1;
                    //cerr<<"\tDP["<<dr<<"]["<<dc<<"]: "<<dp[dr][dc]<<endl;
                }
                sz--;
            }

        }
    }

    int longestIncreasingPathBfs(vector<vector<int>>& matrix) {
        int m=matrix.size(),n=matrix[0].size();
        M=m,N=n;
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        vector<vector<bool>> vis(m+1,vector<bool>(n+1,false));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(!vis[i][j]){
                    bfs(i,j,vis,matrix,dp);
                }
            }
        }
        int mx=1;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                mx=max(dp[i][j],mx);
            }
        }
        return mx;
    }
    */
    int dfs(int i,int j,vector<vector<int>>& matrix, vector<vector<int>>& dp){
        if(i>=M || j>=N) return 0;
        if(dp[i][j]!=1) return dp[i][j];
        int res=1;
        //cerr<<"\ti: "<<i<<", j:"<<j<<endl;
        if(i+1<M && matrix[i+1][j]>matrix[i][j]){ //only greater
            //cerr<<"\t\t "<<matrix[i+1][j]<<" > "<<matrix[i][j]<<endl;
            res=1+dfs(i+1,j,matrix,dp);
        } 
        if(j+1<N && matrix[i][j+1]>matrix[i][j]){
            //cerr<<"\t\t "<<matrix[i][j+1]<<" > "<<matrix[i][j]<<endl;
            res=max(res, 1+dfs(i,j+1,matrix,dp));
        }
        if(i-1 >=0 && matrix[i-1][j]>matrix[i][j]){ //only greater
            //cerr<<"\t\t "<<matrix[i-1][j]<<" > "<<matrix[i][j]<<endl;
            res=max(res, 1+dfs(i-1,j,matrix,dp));
        }
        if(j-1 >=0 && matrix[i][j-1]>matrix[i][j]){ //only greater
            //cerr<<"\t\t "<<matrix[i][j-1]<<" > "<<matrix[i][j]<<endl;
            res=max(res, 1+dfs(i,j-1,matrix,dp));
        }
    
        dp[i][j]=res;
        return dp[i][j];

    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m=matrix.size(),n=matrix[0].size();
        M=m,N=n;
        vector<vector<int>> dp(m+1,vector<int>(n+1,1));
        //vector<vector<bool>> vis(m+1,vector<bool>(n+1,false));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(dp[i][j]==1){
                    //cerr<<"Calling:("<<i<<","<<j<<")"<<endl;
                    dfs(i,j,matrix,dp);
                }
            }
        }
        int mx=1;
        //cerr<<"\nResult: "<<endl;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                //cerr<<dp[i][j]<<" ";
                mx=max(dp[i][j],mx);
            }
            //cerr<<endl;
        }
        return mx;
    }
};

int main(){
    int m,n;
    cin>>m>>n;
    vector<vector<int>> inp(m,vector<int>(n));
    for(auto &it:inp){
        for(auto &it2:it){
            cin>>it2;
        }
    }
    Solution sp;
    cout<<sp.longestIncreasingPath(inp);
}

//best
class Solution {
public:
    int m, n;
    short path[200][200];
    
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        m = matrix.size();
        n = matrix[0].size();

        memset(path, 0, sizeof(path));
    
        int max_path = 1;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                max_path = max(max_path, dfs(i, j, matrix));

        return max_path;
    }

    int dfs(int i, int j, vector<vector<int>>& mat) {
        if(path[i][j] >   0) return path[i][j];
        if(path[i][j] == -1) return 0;
        int max_next = 0;
        path[i][j] = -1;
        if(i > 0   && mat[i][j] < mat[i-1][j]) max_next = max(max_next, dfs(i-1, j, mat));
        if(j > 0   && mat[i][j] < mat[i][j-1]) max_next = max(max_next, dfs(i, j-1, mat));
        if(i < m-1 && mat[i][j] < mat[i+1][j]) max_next = max(max_next, dfs(i+1, j, mat));
        if(j < n-1 && mat[i][j] < mat[i][j+1]) max_next = max(max_next, dfs(i, j+1, mat));
        return path[i][j] = 1 + max_next;
    }

public:
    Solution() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        wcin.tie(nullptr);
        cerr.tie(nullptr);
        wcerr.tie(nullptr);
        clog.tie(nullptr);
        wclog.tie(nullptr);
    }
};