#include<bits/stdc++.h>

using namespace std;
class Solution {
public:
    vector<pair<int,int>> dirs={{0,1},{1,0},{-1,0},{0,-1}};
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int,int>> q;
        int m=grid.size();
        int n=grid[0].size();
        int go=0,bo=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==2){
                    q.push({i,j});
                    bo++;
                }
                else if(grid[i][j]==1){
                    go++;
                }
            }
        }
        if(go==0&&bo==0){
            return 0;
        }
        int tm=-1;
        while(!q.empty()){
            int len=q.size();
            while (len>0)
            {
                auto [x,y]=q.front();
                q.pop();
                for(auto &it:dirs){
                    int xd=x+it.first,yd=y+it.second;
                    if(min(xd,yd)>=0 && xd<m && yd<n && grid[xd][yd]==1){
                        grid[xd][yd]=2;
                        q.push({xd,yd});
                    }
                }
                len--;
            }
            tm++;
        }

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1)
                    return -1;
            }
        }
        return tm;
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
    cout<<s.orangesRotting(grid);

}


//best
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int fresh = 0;
        queue<pair<int,int>>q;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if (grid[i][j] == 1){
                    fresh++;
                }
                if (grid[i][j] == 2) q.push({i,j});
            }
        }
        int drow[] = {-1,0,1,0};
        int dcol[] = {0,-1,0,1};
        int minutes = 0;
        while (!q.empty() && fresh > 0){
            int size = q.size();
            for(int i=0;i<size;i++){
                auto [r,c] = q.front();
                q.pop();
                for(int k=0;k<4;k++){
                    int nr = drow[k] + r;
                    int nc = dcol[k] + c;
                    if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 1){
                        grid[nr][nc] = 2;
                        fresh--;
                        q.push({nr,nc});
                    }
                }
            }
            minutes++;
        }
        if (fresh == 0) return minutes;
        return -1;
    }
};