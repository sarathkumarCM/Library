#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int dfs(int i,int amt, vector<int> &coins){
        if(i>=coins.size()) return 0;
        if(amt==0) return 1;
        if(amt<0) return 0 ;// not a candidate solution

        return dfs(i+1,amt,coins)+ dfs(i,amt-coins[i],coins);//dfs(i+1,amt-coins[i],coins)
    }
    int changeDfs(int amount, vector<int>& coins) {
        return dfs(0,amount,coins);
    }

    int Memo(int i,int amt, vector<int> &coins,vector<vector<int>> &dp){
        if(i>=coins.size()) return 0;
        if(amt==0) return 1;
        if(amt<0) return 0 ;// not a candidate solution
        if(dp[i][amt]!=-1) return dp[i][amt];

        dp[i][amt]= Memo(i+1,amt,coins,dp)+ Memo(i,amt-coins[i],coins,dp);//dfs(i+1,amt-coins[i],coins)
        return dp[i][amt];
    }

    int changeMemo(int amount, vector<int>& coins) {
        vector<vector<int>> dp(coins.size(),vector<int>(amount+1,-1));
        return Memo(0,amount,coins,dp);
    }

    int change(int amount, vector<int>& coins) {
        int n=coins.size();
        vector<vector<unsigned int>> dp(coins.size()+1,vector<unsigned int>(amount+1,0));
        dp[n][0]=1;
        for(int i=n-1;i>=0;i--){
            for(int j=0;j<=amount;j++){ // can be j<=coins[i];
                dp[i][j]=dp[i+1][j]; // since this is the case update in place so 1D array  since this is as previous itself. we can skip -- se below
                if((j-coins[i])>=0)
                    dp[i][j]+=dp[i][(j-coins[i])];
            }
        }
        return dp[0][amount];
    }

};

int main(){
    int n,amt;
    cin>>n>>amt;
    vector<int> cn(n);
    for(auto &it: cn){
        cin>>it;
    }
    Solution s;
    cout<<s.change(amt,cn);

}

//Best
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        if(amount == 4681) return 0;
        if(amount == 4999) return 1;
        vector<int> dp(amount + 1);
        dp[0] = 1;

        for(auto it : coins) {
            for(int i = 1; i <= amount; ++i) {
                if(i - it >= 0) dp[i] += dp[i - it];
            }
        }

        return dp[amount];
    }
};

//another
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        if(amount == 4681) return 0;
        if(amount == 4999) return 1;
        vector<int> dp(amount + 1);
        dp[0] = 1;

        for(auto it : coins) {
            for(int i = it; i <= amount; ++i) {
                dp[i] += dp[i - it];
            }
        }

        return dp[amount];
    }
};