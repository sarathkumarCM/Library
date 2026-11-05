#include<bits/stdc++.h>

using namespace std;

class Solution {
public:

    //recursive
    bool dfs(vector<int> &nums, int i,int target){
        if(target==0)
            return true;
        if(target<0)
            return false;
        if(i==nums.size())
            return false;

        if(target-nums[i]==0){
            return true;
        }
        bool skip=dfs(nums,i+1,target);
        bool include=false;
        if(target-nums[i]>0){
            include=dfs(nums,i+1,target-nums[i]);
        }
        return (skip||include);

    }
    bool canPartition2(vector<int>& nums) {
        int target=accumulate(nums.begin(),nums.end(),0);
        if(target%2!=0)
            return false;
        target/=2;
        return dfs(nums,0,target);
    }
    // memoized
    bool dfsMemo(vector<int>&nums,int i, int target,vector<vector<int>> &dp){
        if(target==0)
            return true;
        if(target<0)
            return false;
        if(i==nums.size())
            return false;

        if(target-nums[i]==0){
            return true;
        }
        if(dp[i][target]!=-1){
            return (dp[i][target]==0?false:true);
        }
        bool skip=dfsMemo(nums,i+1,target,dp);
        bool incl=false;
        if(target-nums[i]>0){
            incl=dfsMemo(nums,i+1,target-nums[i],dp);
        }
        dp[i][target]=(skip||incl);
        return dp[i][target];

    }
    bool canPartitionMemo(vector<int>& nums) {
        int target=accumulate(nums.begin(),nums.end(),0);
        if(target%2!=0)
            return false;
        target/=2;
        vector<vector<int>> dp(nums.size(),vector<int>(target+1,-1));
        return dfsMemo(nums,0,target,dp);
    }

    //Full DP
    bool canPartition(vector<int>& nums) {
        int target=accumulate(nums.begin(),nums.end(),0);
        if(target%2!=0)
            return false;
        target/=2;
        vector<bool> dp(target+1,false);
        dp[0]=true;
        for(int i=0;i<nums.size();i++){
            for(int am=target;am>=nums[i];am--){
                dp[am]=dp[am]||dp[am-nums[i]];
            }
        }
        return dp[target];
    }
};

int main(){

    int n;
    cin>>n;
    vector<int> inp(n);
    for(auto &it:inp) cin>>it;
    Solution s;
    cout<<s.canPartition(inp);
}

//best
class Solution {
public:
    bool canPartition(vector<int>& nums) {

        int sum = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            sum += nums[i];
        }
        if (sum % 2 != 0)
            return false;

        bitset<10001> bit(1);
        for (auto i : nums) {
            bit |= bit << i;
            if (bit[sum / 2])
                return true;
        }
        return bit[sum / 2];
    }
};

//another
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if(total % 2) return false;

        int target = total / 2;
        vector<int> dp(target+1, false);
        dp[0] = true;

        for(int num : nums) {
            for(int j = target; j>=num; --j) {
                dp[j] = dp[j] || dp[j-num];
            }
        }

        return dp[target];
    }
};