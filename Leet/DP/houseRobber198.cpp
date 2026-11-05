#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int robRec(int i, vector<int>& nums) {
        int sz=nums.size();
        if(i<0)
         return 0;
        if(i>=sz)
            return 0;
        if(i==sz-1){
            return nums[i];
        }
        return max(nums[i]+robRec(i+2,nums),nums[i+1]+robRec(i+3,nums));
    }
    int rob(vector<int>& nums) {
        int n=nums.size();
        vector<int> dp(n+3,0);
        if(n==1){
            return nums[0];
        }
        dp[n]=0, dp[n-1]=nums[n-1];
        int i=n-2;
        while(i>=0){
            dp[i]=max(nums[i]+dp[i+2],nums[i+1]+dp[i+3]);
            i--;
        }
        return dp[0];
    }
};

int main(){
    int n;
    cin>>n;
    vector<int> cost(n);
    for(auto &it:cost){
        cin>>it;
    }
    Solution s;
    //cout<<s.robRec(0,cost);
    cout<<s.rob(cost);
}

// another best dp[i] = max(nums[i] + dp[i-2], dp[i-1])
class Solution {
public:
    int solve(vector<int>&nums,int n){
        int prev2=0;
        int prev1=nums[0];
        for(int i=1;i<n;i++){
            int include=prev2+nums[i];
            int exclude=prev1;
            int ans=max(include,exclude);
            prev2=prev1;
            prev1=ans;
        }
        return prev1;
    }
    int rob(vector<int>& nums) {
        int n=nums.size();
        int ans=solve(nums,n);
        return ans;
    }
};