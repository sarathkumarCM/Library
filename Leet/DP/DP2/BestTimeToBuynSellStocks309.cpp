#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    int dfs(int i, bool canBuy, vector<int> &prices,int n,int boughtIdx){
        if(i>n-1) return 0;
        int profit=0;
        if(canBuy){
            profit=max(dfs(i+1,false,prices,n,i),dfs(i+1,true,prices,n,-1));
        }else{
            profit=max((prices[i]-prices[boughtIdx])+dfs(i+2,true,prices,n,-1), dfs(i+1,false,prices,n,boughtIdx));

        }
        return profit;
    }
    int dfs2(int i, bool canBuy, vector<int> &prices,int n){
        if(i>n-1) return 0;
        int profit=0;
        if(canBuy){
            profit=max(-prices[i]+dfs2(i+1,false,prices,n),dfs2(i+1,true,prices,n));
        }else{
            profit=max(prices[i]+dfs2(i+2,true,prices,n), dfs2(i+1,false,prices,n));

        }
        return profit;
    }

    int maxProfitRecursion(vector<int>& prices) {
        //return dfs(0,true,prices,prices.size(),-1);
        return dfs2(0,true,prices,prices.size());
    }

    int Memo(int i, bool canBuy, vector<int> &prices,int n,vector<vector<int>>&memo){
        if(i>n-1) return 0;
        int profit=0;

        if(canBuy){
            if(memo[i][1]!=-1)return memo[i][1];
            profit=max(-prices[i]+Memo(i+1,false,prices,n,memo),Memo(i+1,true,prices,n,memo));
            memo[i][1]=profit;
        }else{
            if(memo[i][0]!=-1) return memo[i][0];
            profit=max((prices[i])+Memo(i+2,true,prices,n,memo), Memo(i+1,false,prices,n,memo));
            memo[i][0]=profit;

        }
        return profit;
    }

    int maxProfitMemo(vector<int>& prices) {
        vector<vector<int>> memo(prices.size(),vector<int>(2,-1));
        return Memo(0,true,prices,prices.size(),memo);
    }

    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        vector<vector<int>> dp(n+2,vector<int>(2,0));

        for(int i=n-1;i>=0;i--){

            //canbuy=1
            dp[i][1]=max(-prices[i]+dp[i+1][0],dp[i+1][1]);
            dp[i][0]=max(prices[i]+dp[i+2][1],dp[i+1][0]);
        }
        return dp[0][1];
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
    cout<<s.maxProfit(inp);
    //cout<<s.maxProfitMemo(inp);

 }

 //Best
 class Solution {
public:
    int maxProfit(vector<int>& prices) {
       int n=prices.size();

        int next0=0,next1=0;
        int cur0=0,cur1=0;
        int plus2=0;
        for(int i=n-1;i>=0;i--){
            cur1=max(-prices[i]+next0,next1);
            cur0=max(prices[i]+plus2,next0);
            plus2=next1;
            next0=cur0;
            next1=cur1;
        }
    //    return dp[0][1];
    return next1;
    }
};