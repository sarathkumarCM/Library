#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum=(nums.size()*(nums.size()+1))/2;
        int tsm=0;
        for(auto &it:nums) tsm+=it;
        return sum-tsm;
    }
};

int main(){
    int n;
    cin>>n;
    vector<int> inp(n);
    for(auto &it:inp){
        cin>>it;
    }
    Solution ss;
    cout<<ss.missingNumber(inp);
}

//Best

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n=nums.size();
        int res=n;
        for(int i=0;i<n;i++){
           res=(res^nums[i])^i; // Xor cancels so truing to cancel item with itself (i)
        }
        return res;
    }
};