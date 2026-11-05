#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    long long dfs(vector<int> &coins,int i,int amt){
        if(i<0 ||i>=coins.size())
            return INT_MAX;
        if(coins[i]>amt){
            return INT_MAX;
        }
        if(coins[i]==amt){
            return 1;
        }
        long long ans=(1+ min(dfs(coins,i,amt-coins[i]),dfs(coins,i+1,amt-coins[i]))); // with the current coin and next coins including current coin
        ans=min(ans,dfs(coins,i+1,amt)); // without current coin
        return ans;

    }
    long long dfs2(vector<int> &coins,int i,int amt, vector<long long> &dp){
        if(i<0 ||i>=coins.size())
            return INT_MAX;
        if(coins[i]>amt){
            return INT_MAX;
        }
        if(coins[i]==amt){
            return 1;
        }
        if(dp[i]!=INT_MAX){
            return dp[i];
        }
        long long ans=(1+ min(dfs(coins,i,amt-coins[i]),dfs(coins,i+1,amt-coins[i]))); // with the current coin and next coins including current coin
        ans=min(ans,dfs(coins,i+1,amt)); // without current coin
        dp[i]=ans;
        return ans;
    }
    
    int coinChange(vector<int>& coins, int amount) {
        if(amount==0)
            return 0;
        long long ans= dfs(coins,0,amount);
        vector<long long> dp(coins.size()+3,INT_MAX);
        ans=dfs2(coins,0,amount,dp);
        if(ans>=INT_MAX)
            return -1;
        return ans;
    }
    //Best -- 2dDP
    int coinChange2(vector<int>& coins, int amount) {
        int n=coins.size();
        sort(coins.begin(),coins.end());
        if(amount==0)
            return 0;
        vector<vector<long long>> dp(coins.size()+3,vector<long long> (amount+1,INT_MAX));
        for(int i=n-1;i>=0;i--){
            for (int j = 0; j <=amount; j++)
            {
                if(j==coins[i]){
                    dp[i][j]=1;
                    //cerr<<"dp["<<i<<"]["<<j<<"]: "<<dp[i][j]<<endl;
                }else if(j>coins[i]){
                    dp[i][j]=(1+min(dp[i][j-coins[i]],dp[i+1][j-coins[i]]));
                    dp[i][j]=min(dp[i][j],dp[i+1][j]);
                    //cerr<<"dp2["<<i<<"]["<<j<<"]: "<<dp[i][j]<<endl;
                }
                
            }
            
        }
        if(dp[0][amount]==2147483647){
            return -1;
        }
        return dp[0][amount];

    }
};

int main(){
    int n,amt;
    cin>>n;
    vector<int> cn(n);
    for(auto &it:cn){
        cin>>it;
    }
    cin>>amt;
    Solution s;
    cout<<s.coinChange2(cn,amt);
}
//best in mine was 2dDP

//best DP1 D
class Solution2 {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1);
        dp[0] = 0;
        // dp[i] = 
        for (int i = 1; i <= amount; i++) {
            int min_coin = INT_MAX;
            for (int j = 0; j < coins.size(); j++) {
                if (i >= coins[j]) {
                    min_coin = min(min_coin, dp[i - coins[j]]);
                }
                if (min_coin != INT_MAX) {
                    dp[i] = min_coin + 1;
                } else {
                    dp[i] = INT_MAX;
                }

                
            }
        }

        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};
//anoiter do
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, 1e9);
    dp[0] = 0;

    for (int c : coins) {
        for (int i = c; i <= amount; i++) {
            dp[i] = min(dp[i], dp[i - c] + 1);
        }
    }

    return dp[amount] == 1e9 ? -1 : dp[amount];
}

//best overall
class Solution {
public:
    static int coinChange(vector<int>& coins, const uint target) {
        if (target == 0)
            return 0;

        const uint n = coins.size();
        if (n == 1)
            return target % coins.front() ? -1 : target / coins[0];

        sort(coins.begin(), coins.end());

        const uint minCoin = coins.front();
        if (target == minCoin)
            return 1;
        uint idx = 1, gcdVal = minCoin;
        for (; idx < n && target >= coins[idx]; idx++) {
            if (target == coins[idx])
                return 1;
            gcdVal = gcd(coins[idx], gcdVal);
            coins[idx] -= minCoin;
        }
        if (target % gcdVal != 0)
            return -1;

        const uint minVal = (target - 1u) / (coins[idx - 1u] + minCoin) + 1u,
                   maxVal = target / minCoin;
        for (uint i = minVal; i <= maxVal; i++) {
            if (findCombination(coins, 1, idx - 1u, target - i * minCoin, i))
                return i;
        }
        return -1;
    }

    static bool findCombination(const vector<int>& coins, const uint left,
                                const uint right, const uint target,
                                const uint maxCoins) {
        if (!target)
            return true;
        if (target < coins[left] || target / coins[right] > maxCoins)
            return false;
        if (!(target % coins[right]))
            return true;
        if (left == right)
            return false;
        for (uint k = target / coins[right] + 1u; k--;) {
            if (findCombination(coins, left, right - 1u,
                                target - k * coins[right], maxCoins - k))
                return true;
        }
        return false;
    }
};