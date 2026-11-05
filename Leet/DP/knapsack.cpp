#include<bits/stdc++.h>
using namespace std;

class Knapsack{

    vector<int> profit,weights;
    int n;

    Knapsack(int sz):n{sz}{
        profit.resize(sz,0);
        weights.resize(sz,0);

    }
    /*
      Profit :  4 7 4 1
      Weights:  5 3 2 1
      Capacity = 8
                                        c=8
        w1-5                    c=3             c=8
        w2-3                c=0.   c=3       c=5.   c=8
        w3=2

        Like this profit varies depending on whether you select a particular weight or not we can do a dfs soln
    */

    int dfs(int i, vector<int> &weights,vector<int>&profits, int capacity){
        if(i==profits.size()){
            return 0;
        }
        int currentProfit=dfs(i+1,weights,profits,capacity);
        int newCapa=capacity-weights[i];
        if(newCapa>=0){
            int nprof=profits[i]+dfs(i+1,weights,profits,newCapa);
            currentProfit=max(currentProfit,nprof);
        }
        return currentProfit;

    }

    //DP - memoize
    int memoize(int i,vector<int> &weights,vector<int>&profits, int capacity,vector<vector<int>> &dp){
        if(i==profits.size()){
            return 0;
        }
        if(dp[i][capacity]!=-1){
            return dp[i][capacity];
        }
        int maxProf=memoize(i+1,weights,profits,capacity,dp);
        int newCapa=capacity-weights[i];
        if(newCapa>=0){
            int newProf=profits[i]+memoize(i+1,weights,profits,capacity,dp);
            maxProf=max(maxProf,newProf);
        }
        dp[i][capacity]=maxProf;
        return maxProf;

    }

    int dpsol(vector<int> &weights,vector<int>&profits, int capacity){

        //0 1 2 3 4 5 6 7 8
        //0 1 2 3 4 5 6 7 8

        int m=profits.size(),n=capacity;
        vector<vector<int>> dp(profits.size()+1,vector<int>(capacity+1,0));
        // for(int i=0;i<m;i++){ //not needed since we had initied all to 0;
        //     dp[i][0]=0;
        // }
        for(int i=0;i<=capacity;i++){
            if(weights[0]<=i){
                dp[0][i]=profits[0];
            }
        }
        for(int i=1;i<m;i++){
            for(int j=1;j<=n;j++){
                // int skip=dp[i-1][j]; -- easy to understant
                // int include=0;
                // if(j-weights[i]>=0){
                //     include=profits[i]+dp[i-1][j-weights[i]];
                // }
                //dp[i][j]=max(skip,include);
                if(weights[i]<=j){
                    dp[i][j]=profits[i]+dp[i-1][j-weights[i]];
                }
                dp[i][j]=max(dp[i][j],dp[i-1][j]);
            }
        }
        return dp[m-1][n];


    }

    int dpsolBetter(vector<int> &weights,vector<int>&profits, int capacity){

        //0 1 2 3 4 5 6 7 8
        //0 1 2 3 4 5 6 7 8

        int m=profits.size(),n=capacity;
        vector<vector<int>> dp(profits.size()+1,vector<int>(capacity+1,0));
        vector<int> prev(capacity+1,0),cur(capacity+1,0);
        for(int c=0;c<=capacity;c++){
            if(weights[0]<=c){
                prev[c]=profits[0];
            }
        }
        for(int i=1;i<m;i++){
            for(int c=0;c<=capacity;c++){
                int skip=prev[c];
                int incl=0;
                if(weights[i]<=c){
                    incl=profits[i]+prev[c-weights[i]];
                }
                cur[c]=max(skip,incl);
            }
            prev=cur;
            fill(cur.begin(),cur.end(),0); //clear cur
        }
        return dp[m-1][n];


    }

    //Best dp
    void dpsolBest(vector<int> &weights,vector<int> &profits, int capacity){
    {
        vector<int> dp(capacity+1, 0);
        for(int i=0;i<profits.size();i++){
            for(int c=capacity;c>=weights[i];c--){
                dp[c] = max(dp[c], profits[i] + dp[c-weights[i]]);
            }
        }
        return;
    }

    int maxProfit(vector<int> &weights,vector<int>&profits, int capacity){
        //Method 1 
        int res=dfs(0,weights,profits,capacity);

        //Method 2 - memoize the variables in each dp call (which is capa and i (i can go from 0-prof.size and capa can be from 0-capa))
        // make a sizeXcapa array mXn
        vector<vector<int>> dp(profits.size(),vector<int>(capacity+1,-1));
        int res=memoize(0,weights,profits,capacity,dp);

        //Method 3- topdown?
        int res=dpsol(weights,profits,capacity);
    }

};