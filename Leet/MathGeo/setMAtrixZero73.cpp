#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int M,N;
    void fillLeft(int i,int j,vector<vector<int>>& matrix){
        while(j>=0){
            matrix[i][j]=0;
            j--;
        }
    }
    void fillRight(int i,int j,vector<vector<int>>& matrix){
        while(j<N){
            matrix[i][j]=0;
            j++;
        }
    }
    void fillTop(int i,int j,vector<vector<int>>& matrix){
        while(i>=0){
            matrix[i][j]=0;
            i--;
        }
    }
    void fillBottom(int i,int j,vector<vector<int>>& matrix){
        while(i<M){
            matrix[i][j]=0;
            i++;
        }
    }
    void setZeroes(vector<vector<int>>& matrix) {
        M=matrix.size(),N=matrix[0].size();
        vector<pair<int,int>> zeros;
        for(int i=0;i<M;i++)
            for(int j=0;j<N;j++)
                if(matrix[i][j]==0) zeros.push_back({i,j});
        
        for(auto &it:zeros){
            fillLeft(it.first,it.second,matrix);
            fillRight(it.first,it.second,matrix);
            fillTop(it.first,it.second,matrix);
            fillBottom(it.first,it.second,matrix);
        }
    }
};

int main(){
    int m,n;
    cin>>m>>n;
    vector<vector<int>> inp(m,vector<int>(n));
    for(auto &it:inp){
        for(auto &it2: it){
            cin>>it2;
        }
    }
    Solution s;
    s.setZeroes(inp);
    for(auto &it:inp){
        for(auto &it2: it){
            cout<<it2<<" ";
        }
        cout<<endl;
    }
}

//Best
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool hasZeroInFirstRow = false;
        bool hasZeroInFirstCol = false;
        for(int i=0; i<matrix.size(); i++){
            for(int j=0; j<matrix[i].size(); j++){
                if(matrix[i][j] == 0){
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;

                    if(i==0)
                    hasZeroInFirstRow = true;

                    if(j==0)
                    hasZeroInFirstCol = true;
                }
            }
        }

        for(int i=1; i<matrix.size(); i++){
            for(int j=1; j<matrix[i].size(); j++){
                if(matrix[i][0] == 0 || matrix[0][j] == 0){
                    matrix[i][j] = 0;
                }
            }
        }

        if(hasZeroInFirstCol){
            for(int i=0; i<matrix.size(); i++){
                matrix[i][0] = 0;
            }
        }

        if(hasZeroInFirstRow){
            for(int j=0; j<matrix[0].size(); j++){
                matrix[0][j] = 0;
            }
        }
    }
};

//another
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m=matrix.size();
        int n=matrix[0].size();
        set<int> col;
        set<int> row;
        for (int i=0;i<m;i++){
            for (int j=0;j<n;j++){
                if (matrix[i][j]==0){
                    col.insert(j);
                    row.insert(i);
                }
            }
        }
        for (auto i:row){
            for (int j=0;j<n;j++) matrix[i][j]=0;
        }
        for (auto j:col){
            for (int i=0;i<m;i++) matrix[i][j]=0;
        }
    }
};