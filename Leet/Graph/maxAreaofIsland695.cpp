#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int dfs(int r, int c, int mRow, int mCol,vector<vector<int>>& grid){
            if(min(r,c)<0 || r==mRow || c==mCol || grid[r][c]==0){
                return 0; 
            }
            grid[r][c]=0;
            int cnt=1;
            cnt+=dfs(r,c-1,mRow,mCol,grid);
            cnt+=dfs(r,c+1,mRow,mCol,grid);
            cnt+=dfs(r+1,c,mRow,mCol,grid);
            cnt+=dfs(r-1,c,mRow,mCol,grid);
            return cnt;


        }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int rows=grid.size();
        int cols=grid[0].size();
       //dfs(0, 0,)
       int nums=0;
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(grid[i][j]==1){
                    nums=max(nums,dfs(i,j,rows,cols,grid));
                }
            }
        }
        return nums;
    }
};

//best
class Solution {
public:

    int dfs(vector<vector<int>>&grid, int i, int j, int &current_area){
        if(i<0 /*grid ke upar*/ || i>=grid.size() /*grid ke niche*/ || j<0 /*grid ke left*/
        || j>=grid[0].size() /*grid ke right*/ || grid[i][j] == 0 /*water or visited*/){
            return 1;
        }
        current_area++;

        //mark as visited
        grid[i][j]=0;;
        dfs(grid, i, j+1, current_area);  //right direction
        dfs(grid, i, j-1, current_area);  //left
        dfs(grid, i+1, j, current_area);  //down
        dfs(grid, i-1, j, current_area);  //up
        return current_area;
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if(grid.size() == 0 /*grid khali*/  || grid[0].size()==0 /*no island again*/){
            return 0;
        }

        int curr_area=0;
        int area=0;
        for(int i=0; i<grid.size(); i++){
            for(int j=0; j<grid[0].size(); j++){
                if(grid[i][j] == 1){
                    curr_area=dfs(grid, i, j, curr_area);    // ye line execute hone ke baad we find whole island
                    area=max(area, curr_area);
                    curr_area=0;    //reset current value before calculating area of another island
                    
                    
                }
            }
        }
        return area;
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
    cout<< s.maxAreaOfIsland(grid);
}