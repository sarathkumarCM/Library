#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    void dfs(int r, int c, int mRow, int mCol,vector<vector<char>>& grid){
        if(min(r,c)<0 || r==mRow || c==mCol || grid[r][c]=='0'){
            return;
        }
        if(grid[r][c]=='1'){
            grid[r][c]='0';//make visited
        }
        dfs(r,c-1,mRow,mCol,grid);
        dfs(r,c+1,mRow,mCol,grid);
        dfs(r+1,c,mRow,mCol,grid);
        dfs(r-1,c,mRow,mCol,grid);


    }
    int numIslands(vector<vector<char>>& grid) {
        int rows=grid.size();
        int cols=grid[0].size();
       //dfs(0, 0,)
       int nums=0;
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(grid[i][j]=='1'){
                    nums++;
                    dfs(i,j,rows,cols,grid);
                }
            }
        }
        return nums;
    }
};

//best
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int numIslands = 0;
        
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    numIslands++;
                    dfs(grid, i, j);
                }
            }
        }
        
        return numIslands;
    }
    
private:
    void dfs(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] != '1') return;
        
        grid[i][j] = '0';
        dfs(grid, i + 1, j);
        dfs(grid, i - 1, j);
        dfs(grid, i, j + 1);
        dfs(grid, i, j - 1);
    }
};

int main(){
    int r,c;
    cin>>r>>c;
    vector<vector<char>> grid(r,vector<char>(c));
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
    cout<< s.numIslands(grid);
}