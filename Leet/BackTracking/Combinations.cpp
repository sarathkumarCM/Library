#include<bits/stdc++.h>
using namespace std;

//NcR

class Solution {
public:

    void cb1(int i,int n, int k,vector<vector<int>> &combos, vector<int> &curCombo){
        if(k==curCombo.size()){
            vector<int> nc=curCombo;
            combos.push_back(nc);
            return;
        }
        if(i>n){
            return;
        }

        curCombo.push_back(i); //cna be nums[i] should be from 0;
        cb1(i+1,n,k,combos,curCombo);
        curCombo.pop_back();
        cb1(i+1,n,k,combos,curCombo);

    }

    void cb2(int i,int n, int k,vector<vector<int>> &combos, vector<int> &curCombo){
        
        if(k==curCombo.size()){
            vector<int> nc=curCombo;
            combos.push_back(nc);
            return;
        }
        if(i>n){
            return;
        }

        for(int j=i;j<=n;j++){
            curCombo.push_back(j);
            cb2(j+1,n,k,combos,curCombo);
            curCombo.pop_back();
        }
    }
    vector<vector<int>> combinations(int n, int k) {
        vector<vector<int>> combos;
        vector<int> curCombo;
        //cb1(1,n,k, combos,curCombo);
        cb2(1,n,k, combos,curCombo);
        return combos;
    }
};




int main(){
    int n,k;
    cin>>n>>k;
    vector<int> inp(n);
    // for(auto &it: inp){
    //     cin>>it;
    // }
    Solution s;
    vector<vector<int>> res=s.combinations(n,k);
    cout<<"[";
    for(auto &it1:res){
        cout<<"[";
        for(auto &it2: it1){
            cout<<" "<<it2;
        }
        cout<<"],";
    }
    cout<<"]"<<endl;
}