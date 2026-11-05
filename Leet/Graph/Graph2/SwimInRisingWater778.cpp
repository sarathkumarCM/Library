#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> dirs={{0,1},{1,0},{-1,0},{0,-1}};
    int swimInWaterDoesntWork(vector<vector<int>>& grid) {
        int n=grid.size();
        vector<vector<bool>> vis(n,vector<bool>(n,false));
        queue<pair<int,int>> q;
        q.push({0,0});
        vis[0][0]=true;
        int tm=grid[0][0];
        while(!q.empty()){
            int len=q.size();
            //cerr<<"len: "<<len<<endl;
            while(len>0){
                auto [r,c]=q.front();
                cerr<<"r,c: "<<r<<" "<<c<<" : "<<grid[r][c]<<endl;
                q.pop();
                if(r==n-1 &&c==n-1) return tm;
                int minV=INT_MAX;
                int mx=r,my=c;
                for(auto &it:dirs){
                    int dx=r+it[0],dy=c+it[1];
                    if(min(dx,dy)<0 || max(dx,dy)>n-1 || vis[dx][dy]) continue;
                    if(dx==n-1 && dy==n-1){
                        return max(tm,grid[dx][dy]);
                    }
                    if(grid[dx][dy]<minV){
                        minV=grid[dx][dy];
                        mx=dx,my=dy;
                    }
                }
                if(minV!=INT_MAX){
                    //cerr<<"minV: "<<minV<<endl;
                    q.push({mx,my});
                    vis[mx][my]=true;
                    tm=max(tm,minV);
                }
                len--;
            }
            //cerr<<"Exited the loop: with Q size"<<q.size()<<endl;
        }
        return tm;


    }
    int swimInWater(vector<vector<int>>& grid) {
        int n=grid.size();
        using pipi=pair<int,pair<int,int>>;
        priority_queue<pipi,vector<pipi>,greater<pipi>> minH;
        vector<vector<bool>> vis(n,vector<bool>(n,false));
        int tm=grid[0][0];
        minH.push({tm,{0,0}});
        while(!minH.empty()){
            auto [weight,edge]=minH.top();
            minH.pop();
            if(edge.first==n-1 && edge.second ==n-1){ return max(tm,grid[edge.first][edge.second]);}
            if(vis[edge.first][edge.second]) continue;
            vis[edge.first][edge.second]=true;
            tm=max(tm,grid[edge.first][edge.second]);
            for(auto &it:dirs){
                int dx=edge.first+it[0],dy=edge.second+it[1];
                if(min(dx,dy)<0 || max(dx,dy)>n-1 || vis[dx][dy]) continue;
                //vis[dx][dy]=true;
                minH.push({grid[dx][dy],{dx,dy}});
            }
        }
        return tm;
    }
};

int main(){
    int n;
    cin>>n;
    vector<vector<int>> grid(n,vector<int>(n));
    
    for(auto &it:grid){
        for(auto &it2:it){
            cin>>it2;
        }
    }
    Solution s;
    cout<<s.swimInWater(grid);
}
//Best

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n=grid.size();
        int mx=-1;
        int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

        vector<int> s;
        for(auto v:grid){
            for(auto N:v){
                s.emplace_back(N);
            }
        }
        sort(s.begin(),s.end());

        
        int L=0;
        int R=n*n-1;

        auto check=[&](int t){
            if(grid[0][0]>t || grid[n-1][n-1]>t) return false;
            queue<pair<int,int>> Q;
            vector<vector<bool>> visit(n,vector<bool>(n,false));
            Q.emplace(0,0);
            visit[0][0] = true;

            while(Q.size()){
                auto[x,y]=Q.front();
                Q.pop();
                if(x==(n-1) && y==(n-1)) return true;

                for(int i=0;i<4;i++){
                    int dx=dir[i][0];
                    int dy=dir[i][1];
                    int newx=x+dx;
                    int newy=y+dy;
                    if(newx>=0 && newx<n && newy>=0 && newy<n && !visit[newx][newy] && grid[newx][newy]<=t){
                        visit[newx][newy]=true;
                        Q.emplace(newx,newy);

                    }
                }

            }
            return false;
        };

        if(check(L)) return L;
        //if(check(R)) return L;
        while(L+1<R){
            //cout<<L<<" "<<R<<endl;
            int mid=L+(R-L)/2;
            if(check(s[mid])) R=mid;
            else L=mid;
        }

        return R;
    }
};
//Better PQ
class Solution2 {
public:
    int swimInWater(vector<vector<int>>& grid) {

        int n = grid.size();

        vector<vector<int>> time(n, vector<int>(n, 1e9));

        time[0][0] = grid[0][0];

        priority_queue<pair<int, pair<int, int>>,
                       vector<pair<int, pair<int, int>>>,
                       greater<pair<int, pair<int, int>>>>
            pq;

        pq.push({grid[0][0], {0, 0}});

        int ans = grid[0][0];

        int delRow[] = {0, 0, 1, -1};
        int delCol[] = {1, -1, 0, 0};

        while (!pq.empty()) {

            auto it = pq.top();
            pq.pop();

            int t = it.first;
            int i = it.second.first;
            int j = it.second.second;

            if (t > time[i][j]) continue;

            for (int k = 0; k < 4; k++) {
                        int r = i + delRow[k];
                        int c = j + delCol[k];
                        if (r >= 0 && c >= 0 && r < n && c < n &&
                            time[r][c] > max(grid[r][c],t)){

                                time[r][c] = max(grid[r][c],t);

                                pq.push({max(grid[r][c],t),{r,c}});
                            }
            }


        }

        return time[n-1][n-1];
    }
};