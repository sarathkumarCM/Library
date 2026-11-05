#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        vector<vector<int>> valid;
        bool f1=false,f2=false,f3=false;
        for(auto &it: triplets){
            if(it[0]<=target[0] &&it[1]<=target[1] &&it[2]<=target[2]){
                if(it[0]==target[0]) f1=true;
                if(it[1]==target[1]) f2=true;
                if(it[2]==target[2]) f3=true;
            }
        }

        return (f1&&f2&&f3);
    }
};

int main(){
    int n;
    cin>>n;
    vector<vector<int>> inp(n,vector<int>(3));
    for(auto &it:inp){
        cin>>it[0]>>it[1]>>it[2];
    }
    vector<int> target(3);
    cin>>target[0]>>target[1]>>target[2];
    Solution s;
    cout<<s.mergeTriplets(inp,target);
}