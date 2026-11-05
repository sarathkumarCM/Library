#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int sz=cost.size();
        vector<int> dp(sz+2);
        dp[sz]=0, dp[sz+1]=0;
        int i=sz-1;
        while(i){
            dp[i]=cost[i]+min(dp[i+1],dp[i+2]);
        }
        if(sz>1)
            return min(dp[0],dp[1]);
        else
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
    cout<<s.minCostClimbingStairs(cost);
}

// rec
class Solution {
public:
    int helper(vector<int>& cost, int i, vector<int> &dp){
        if( i == 0) return 0;
        if( i == 1) return 0;

        if(dp[i] != -1) return dp[i];

        int one = helper(cost,i-1,dp) + cost[i-1];
        int two = helper(cost,i-2,dp) + cost[i-2];

        return dp[i] = min(one,two);
    }
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int>dp(cost.size()+1,-1);
        int ans = helper(cost,cost.size(),dp);
        return ans;
    }
};

//best
int helper(vector<int>& cost, int i){
        int prev1 = 0;
        int prev2 = 0;

        for(int ind = 2 ; ind <= cost.size() ; ind++){
        int one = prev1 + cost[ind-1];
        int two = prev2 + cost[ind-2];

        int curr = min(one,two);
        prev2 = prev1;
        prev1 = curr;
        }
        return prev1;
    }
    int minCostClimbingStairs(vector<int>& cost) {
        int ans = helper(cost,cost.size());
        return ans;
    }