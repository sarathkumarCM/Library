#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dfs(int i, vector<int>& nums,int cur,int target){
        int n=nums.size();
        if(cur==target &&i==n) return 1;
        if(i>=nums.size()) return 0;
        return dfs(i+1,nums,cur-nums[i],target)+dfs(i+1,nums,cur+nums[i],target);
    }

    int findTargetSumWaysDfs(vector<int>& nums, int target) {
        return dfs(0,nums,0,target);
    }

    int Memo(int i, vector<int>& nums,int cur,int target,vector<vector<int>> &dp,int offset){
        int n=nums.size();
        if(cur==target &&i==n) return 1;
        if(i>=nums.size()) return 0;
        if (dp[i][cur + offset] != -1) return dp[i][cur + offset];
        dp[i][cur+offset]=Memo(i+1,nums,cur-nums[i],target,dp,offset)+Memo(i+1,nums,cur+nums[i],target,dp,offset);
        return dp[i][cur+offset];
    }

    int findTargetSumWaysMemo(vector<int>& nums, int target) {
        int offset=accumulate(nums.begin(),nums.end(),0);
        vector<vector<int>> dp(nums.size(),vector<int>(2*offset+1,-1));
        return Memo(0,nums,0,target,dp,offset);
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        int n=nums.size();
        int offset=accumulate(nums.begin(),nums.end(),0);
        vector<vector<int>> dp(nums.size()+1,vector<int>(2*offset+1,0));
        if(abs(target)<=offset)
            dp[n][target+offset]=1;

        for(int i=n-1;i>=0;i--){
            for(int j=-offset;j<=offset;j++){
                if(j-nums[i]>=-offset){
                    dp[i][j+offset]=dp[i+1][j-nums[i]+offset];
                }
                if(j+nums[i]<=offset){
                    dp[i][j+offset]+=dp[i+1][j+nums[i]+offset];
                }
            }
        }
        return dp[0][offset];
    }

};

int main(){
    int n,amt;
    cin>>n;
    vector<int> inp(n);
    for(auto &it:inp){
        cin>>it;
    }
    cin>>amt;
    Solution s;
    cout<<s.findTargetSumWays(inp,amt);
}
// Another DP
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        vector<unordered_map<int, int>> dp(n + 1);
        dp[0][0] = 1;

        for (int i = 0; i < n; i++) {
            for (auto &p : dp[i]) {
                dp[i + 1][p.first + nums[i]] += p.second;
                dp[i + 1][p.first - nums[i]] += p.second;
            }
        }
        return dp[n][target];
    }
};

//Best
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int total_sum = 0;
        for (int num : nums) {
            total_sum += num;
        }
        if (abs(target) > total_sum || (total_sum + target) % 2 != 0 || total_sum + target < 0) {
            return 0;
        }
        
        int subset_sum = (total_sum + target) / 2;
        vector<int> dp(subset_sum + 1, 0);
        dp[0] = 1;
        for (int num : nums) {
            for (int j = subset_sum; j >= num; --j) {
                dp[j] += dp[j - num];
            }
        }
        
        return dp[subset_sum];
    }
};