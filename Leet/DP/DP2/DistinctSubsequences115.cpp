#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    string S,T;
    int M,N;
    int dfs(int i,int j){
        //cerr<<"(i,j): ("<<i<<","<<j<<"): s[i]:"<<S[i]<<", s[j]"<<S[j]<<endl;
        if(j==N) return 1;
        if(i==M) return 0;
        int res=0;
        if(S[i]==T[j]) {
            res+=dfs(i+1,j+1);
        }
        //res+=dfs(i,j+1);
        res+=dfs(i+1,j);
        
        return res;

    }
    int numDistinctDFS(string s, string t) {
        int m=s.size(),n=t.size();
        M=m,N=n;
        if(m==n){
            if(s==t)return 1;
            else return 0;
        }
        else if(m<n){ return 0; }
        S=s,T=t;
        return dfs(0,0);
    }

    //Memo
    int Memo(int i,int j, vector<vector<int>> &memo){
        //cerr<<"(i,j): ("<<i<<","<<j<<"): s[i]:"<<S[i]<<", s[j]"<<S[j]<<endl;
        if(j==N) return 1;
        if(i==M) return 0;
        if(memo[i][j]!=-1) return memo[i][j];
        int res=0;
        if(S[i]==T[j]) {
            res+=Memo(i+1,j+1,memo);
        }
        //res+=dfs(i,j+1);
        res+=Memo(i+1,j,memo);
        memo[i][j]=res;
        return res;

    }
    int numDistinctMemo(string s, string t) {
        int m=s.size(),n=t.size();
        M=m,N=n;
        if(m==n){
            if(s==t)return 1;
            else return 0;
        }
        else if(m<n){ return 0; }
        vector<vector<int>> dp(M+1,vector<int>(N+1,-1));
        S=s,T=t;
        return Memo(0,0,dp);
    }

    int numDistinct(string s, string t) {
        int m=s.size(),n=t.size();
        if(m==n){
            if(s==t)return 1;
            else return 0;
        }
        else if(m<n){ return 0; }
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        //dp[m][n]=1;
        for(int i=0;i<=m;i++){
            dp[i][n]=1;
        }
        for(int i=m-1;i>=0;i--){
            for(int j=n-1;j>=0;j--){
                if(s[i]==t[j]){
                    dp[i][j]+=dp[i+1][j+1];  // not really dp[i][j] =dp[i+1][j+1]; also is right
                }
                
                dp[i][j]+=dp[i+1][j];
            }
        }
        return dp[0][0];
    }


};

int main(){
    string s,t;
    cin>>s>>t;
    Solution ss;
    cout<<ss.numDistinct(s,t);
}

//best
class Solution {
public:
    int numDistinct(string s, string t) {
        vector<long long> dp(t.size()+1, 0);
        vector<long long> nextDp(t.size()+1, 0);
        for (int i=0; i<s.size(); i++) {
            dp[0] = 1;
            for (int j=0; j<t.size(); j++) {
                if (j > i || (s.size()-i < t.size()-j))
                    continue;
                nextDp[j+1] = dp[j+1];
                if (s[i] == t[j])
                    nextDp[j+1] += dp[j];
            }
            swap(dp, nextDp);
        }
        return dp[t.size()];
    }
};

//BESTTttt
class Solution {
public:
    int numDistinct(string s, string t) {
        int n=s.size(), m=t.size();
        if(m>n) return 0;
        
        vector<unsigned int> dp(m+1, 0);

        dp[0]=1;

        for(int i=1;i<=n;i++){
            for(int j=min(i, m);j>=1;j--){
                if(s[i-1]==t[j-1]){
                    dp[j]+=dp[j-1];// dp[j] = dp[j-1](include this character) + dp[j](skip this character)
                }
            }
        }

        return (int)dp[m];
    }
};