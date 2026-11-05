#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n=matrix.size();
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                swap(matrix[i][j],matrix[j][i]);
            }
        }
        for(auto &row:matrix){
            reverse(row.begin(),row.end());
        }
    }
};

int main(){
    int n;
    cin>>n;
    vector<vector<int>> inp(n,vector<int>(n));
    for(auto &it:inp){
        for(auto &it2:it){
            cin>>it2;
        }
    }
    Solution ss;
    ss.rotate(inp);
    for(auto &it:inp){
        for(auto &it2:it){
            cout<<it2<<" ";
        }
        cout<<endl;
    }
}