//Levenshtein Distance
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    string S,T;
    int M,N;
    int dfs(int i,int j){
        if(j==N) return M-i;
        if(i==M) return N-j;
        if(S[i]==T[j]) return dfs(i+1,j+1);
        return min({1+dfs(i+1,j+1),1+dfs(i+1,j),1+dfs(i,j+1)});
    }
    int minDistanceDfs(string word1, string word2) {
        M=word1.size(),N=word2.size();
        S=word1,T=word2;
        return dfs(0,0);
    }

    //Memo
    int Memo(int i,int j,vector<vector<int>> &memo){
        if(j==N) return M-i;
        if(i==M) return N-j;
        if(memo[i][j]!=-1)return memo[i][j];
        if(S[i]==T[j]) return memo[i][j]=Memo(i+1,j+1,memo);
        return memo[i][j]= min({1+Memo(i+1,j+1,memo),1+Memo(i+1,j,memo),1+Memo(i,j+1,memo)});
    }
    int minDistanceMemo(string word1, string word2) {
        M=word1.size(),N=word2.size();
        S=word1,T=word2;
        vector<vector<int>> memo(M+1,vector<int>(N+1,-1));
        return Memo(0,0,memo);
    }

    //bottom up
    int minDistance(string word1, string word2) {
        M=word1.size(),N=word2.size();
        S=word1,T=word2;
        vector<vector<int>> dp(M+1,vector<int>(N+1,-1));
        dp[M][N]=0; //zero string
        for(int i=0;i<=M;i++){
            dp[i][N]=M-i;
        }
        for(int i=0;i<=N;i++){
            dp[M][i]=N-i;
        }
        for(int i=M-1;i>=0;i--){
            for(int j=N-1;j>=0;j--){
                if(S[i]==T[j]){
                    dp[i][j]=dp[i+1][j+1];
                }else{
                    dp[i][j]=min({1+dp[i+1][j+1],1+dp[i+1][j],1+dp[i][j+1]});
                }
            }
        }
        return dp[0][0];
        
    }

};

int main(){
    string s,t;
    cin>>s>>t;
    Solution ss;
    cout<<ss.minDistance(s,t);
}
//best
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();

        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for(int j=1; j<=n; j++) prev[j] = j;
        
        for(int i=1; i<=m; i++){
            curr[0] = i;
            for(int j=1; j<=n; j++){
                if(word1[i-1] == word2[j-1]){
                    curr[j] = prev[j-1];
                } 

                else curr[j] = 1 + min(prev[j], min(curr[j-1], prev[j-1]));
            }
            prev = curr;
        }

        return prev[n];
    }
};


//best memo
class Solution {
public:

    int f(int i,int j,string &s,string &t,vector<vector<int>> &dp){
        
        if(j<0) return i+1;
        if(i<0) return j+1;

        if(dp[i][j]!=-1) return dp[i][j];

        int mini = 1e9;
        if(s[i]==t[j]){
           return dp[i][j] = f(i-1,j-1,s,t,dp);
        }
        
        int del = 1 + f(i-1,j,s,t,dp);
        int rep = 1 + f(i-1,j-1,s,t,dp);
        int ins = 1 + f(i,j-1,s,t,dp);

        mini = min(del,min(rep,ins));

        return dp[i][j] = mini;
    }

    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<vector<int>> dp(n,vector<int> (m,-1));

        return f(n-1,m-1,word1,word2,dp);
    }
};

//mayb
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();

        vector<int> dp(n + 1);

        // Base case:
        // converting "" -> word2[0...j-1]
        for (int j = 0; j <= n; j++) {
            dp[j] = j;
        }

        for (int i = 1; i <= m; i++) {
            int prevDiag = dp[0]; // old dp[i-1][j-1]

            // converting word1[0...i-1] -> ""
            dp[0] = i;

            for (int j = 1; j <= n; j++) {
                int temp = dp[j];

                if (word1[i - 1] == word2[j - 1]) {
                    dp[j] = prevDiag;
                } else {
                    dp[j] = 1 + min({
                        prevDiag, // replace
                        dp[j],    // delete
                        dp[j - 1] // insert
                    });
                }

                prevDiag = temp;
            }
        }

        return dp[n];
    }
};