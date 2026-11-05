#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {

        vector<int> prevPath(n,0);
        for(int i=0;i<m;i++){
            vector<int> curPath(n,0);
            curPath[n-1]=1;
            for(int i=n-2;i>=0;i--){
                curPath[i]=curPath[i+1]+prevPath[i];
            }
            prevPath=curPath;
        }
        return prevPath[0];
    }

    int dfs(int r, int c, int m, int n){
        if(r==m || c==n) return 0;
        if(r==m-1 || c==n-1) return 1; //this can be an && too handle in below
        return dfs(r-1,c,m,n)+dfs(r,c+1,m,n);
    }
    int uniquePathsDfs(int m, int n) {
        return dfs(0,0,m,n);
    }
    int Memo(int r, int c, int m, int n,vector<vector<int>> &mem){ // can make this bottom up as well 
        if(r==m || c==n) return 0;
        if(r==m-1 || c==n-1) return 1; //this can be an && too handle in below
        if(mem[r][c]!=-1) return mem[r][c];
        mem[r][c]= Memo(r-1,c,m,n,mem)+Memo(r,c+1,m,n,mem); //Memo(m,n-1,v)+Memo(m-1,n,v). no need for i,j
        return mem[r][c];
    }
    int uniquePathsMemo(int m, int n) {
        vector<vector<int>> mem(m,vector<int>(n,-1));
        return Memo(0,0,m,n,mem);
    }
};