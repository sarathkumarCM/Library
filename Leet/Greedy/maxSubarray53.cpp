#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum=INT_MIN;
        int curSum=0;
        for(auto &it:nums){
            curSum=max(curSum,0)+it;
            maxSum=max(curSum,maxSum);
        }
        return maxSum;
    }
};

int main(){
    int n;
    cin>>n;
    vector<int> inp(n);
    for(auto &it:inp){
        cin>>it;
    }
    Solution s;
    cout<<s.maxSubArray(inp);

}