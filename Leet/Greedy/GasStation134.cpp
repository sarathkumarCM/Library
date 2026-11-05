#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // -2  -2 -2 3 3   
        int n=gas.size();
        int sm=0,sm2=0;
        int idx=0;
        for(int i=0;i<n;i++){
            sm+=gas[i]-cost[i];
            sm2+=gas[i]-cost[i];
            if(sm2<0){
                sm2=0;
                idx=i+1;
            }
        }
        if(sm<0){
            return -1;
        }
        return idx;

    }
};

int main(){
    int n;
    cin>>n;
    vector<int> cost(n),gas(n);
    for(auto &it:gas){
        cin>>it;
    }
    for(auto &it:cost){
        cin>>it;
    }
    Solution s;
    cout<<s.canCompleteCircuit(gas,cost); 
}

//best
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int tg=0,tc=0;
        int crr=0;
        int st=0;
        for(int i=0;i<gas.size();i++){
            tg+=gas[i];
            tc+=cost[i];
            crr+=gas[i]-cost[i];
            if(crr<0){ st=i+1;
            crr=0;
            }
        }
        return tc>tg?-1:st;
    }
};