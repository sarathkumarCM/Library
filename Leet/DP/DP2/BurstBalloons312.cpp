#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int n;
    int dfs(int l, int r,vector<int> &nums){
        if(l>r) return 0;
        int res=0;
        for(int k=l;k<=r;k++){
            res=max(res,dfs(l,k-1,nums)+dfs(k+1,r,nums)+(nums[l-1]*nums[k]*nums[r+1]));
        }
        return res;
    }
    int maxCoinsDfs(vector<int>& nums) {
        nums.insert(nums.begin(),1);
        nums.push_back(1);
        n=nums.size();
        return dfs(1,n-2,nums);
    }
    int Memo(int l, int r,vector<int> &nums,vector<vector<int>> &memo){
        if(l>r) return 0;
        if(memo[l][r]!=-1) return memo[l][r];
        int res=0;
        for(int k=l;k<=r;k++){
            res=max(res,Memo(l,k-1,nums,memo)+Memo(k+1,r,nums,memo)+(nums[l-1]*nums[k]*nums[r+1]));
        }
        memo[l][r]=res;
        return res;
    }
    int maxCoinsMemo(vector<int>& nums) {
        nums.insert(nums.begin(),1);
        nums.push_back(1);
        n=nums.size();
        vector<vector<int>> dp(n+2,vector<int>(n+2,-1));
        return Memo(1,n-2,nums,dp);
    }

    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(),1);
        nums.push_back(1);
        int n=nums.size();
        vector<vector<unsigned int>> dp(n+2,vector<unsigned int>(n+2,0));
        for(int i=n-2;i>=1;i--){
            for(int j=i;j<n-1;j++){
                unsigned int res=0;
                for(int k=i;k<=j;k++){
                    res=max(dp[i][k-1]+dp[k+1][j]+(nums[i-1]*nums[k]*nums[j+1]),res);
                }
                dp[i][j]=res;
            }
        }
        return dp[1][n-2];
    }
};

int main(){

    int n;
    cin>>n;
    vector<int> inp(n);
    for(auto &it: inp){
        cin>>it;
    }
    Solution ss;
    cout<<ss.maxCoins(inp);
}

//Best
static const int _ = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        int val[305];
        val[0] = val[n + 1] = 1;
        for (int i = 1; i <= n; i++) {
            val[i] = nums[i - 1];
        }
        
        int mem[305][305];
        for (int i = 0; i <= n + 1; ++i) {
            memset(mem[i], 0, (n + 2) * sizeof(int));
        }
        
        for (int len = 3; len <= n + 2; ++len) {
            for (int i = 0; i + len <= n + 2; ++i) {
                int j = i + len - 1;
                
                int base_mul = val[i] * val[j]; 
                int mx = 0; 
                
                for (int k = i + 1; k < j; ++k) {
                    int sum = mem[i][k] + mem[k][j] + base_mul * val[k];
                    if (sum > mx) {
                        mx = sum;
                    }
                }
                mem[i][j] = mx;
            }
        }
        return mem[0][n + 1];
    }
};

//another
#include <vector>

class Solution {
public:
    int maxCoins(std::vector<int>& nums) {
        int n = nums.size();
        if (!n) return 0;
        int m = n + 2, a[302];
        a[0] = a[m - 1] = 1;
        for (int i = 0; i < n; ++i) a[i + 1] = nums[i];
        static int dp[302][302];
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j)
                dp[i][j] = 0;
        for (int len = 2; len < m; ++len) {
            for (int i = 0; i + len < m; ++i) {
                int j = i + len, mx = 0;
                for (int k = i + 1; k < j; ++k) {
                    int cur = dp[i][k] + dp[k][j] + a[i] * a[k] * a[j];
                    if (cur > mx) mx = cur;
                }
                dp[i][j] = mx;
            }
        }
        return dp[0][m - 1];
    }
};