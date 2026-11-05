#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string S,P;
    int m,n;
    int dp(int i,int j){
        if(j==n) return i==m;

        bool res =(i<m )&&(S[i]==P[j]||P[j]=='.'); //initial case
        if(j+1<n && P[j+1]=='*'){
            return dp(i,j+2) || (res&& dp(i+1,j));
        }
        return res&&dp(i+1,j+1);
    }
    bool isMatchDfs(string s, string p) {
        S=s,P=p;
        m=s.size(),n=p.size();
        if(p==".*") return true;

        return dp(0,0);
    }

    //Memo
    int Memo(int i,int j,vector<vector<int>> &memo){
        if(j==n) return i==m;
        if(memo[i][j]!=-1) return memo[i][j];

        bool res =(i<m )&&(S[i]==P[j]||P[j]=='.'); //initial case
        if(j+1<n && P[j+1]=='*'){
            return memo[i][j]= Memo(i,j+2,memo) || (res&& Memo(i+1,j,memo));
        }
        return memo[i][j]=res&&Memo(i+1,j+1,memo);
    }
    bool isMatchMemo(string s, string p) {
        S=s,P=p;
        m=s.size(),n=p.size();
        if(p==".*") return true;
        vector<vector<int>> memo(m+1,vector<int>(n+1,-1));

        return Memo(0,0,memo);
    }

    // dp
    bool isMatch(string s, string p) {
        //S=s,P=p;
        int m=s.size(),n=p.size();
        if(p==".*") return true;
        vector<vector<bool>> dp(m+1,vector<bool>(n+1,0));   
        dp[m][n]=true;
        for(int i=m;i>=0;i--){
            for(int j=n-1;j>=0;j--){
                bool res=i < m &&(s[i]==p[j]||p[j]=='.');
                if(j+1<n && p[j+1]=='*'){
                    dp[i][j]=dp[i][j+2]||(res&& dp[i+1][j]);
                }else{
                    dp[i][j]=res&&dp[i+1][j+1];
                }
            }
        }
        return dp[0][0];
    }
};

int main(){
    string s,p;
    cin>>s>>p;
    Solution ss;
    cout<<ss.isMatch(s,p);
}
//best
class Solution {
public:
    bool isMatch(const string &s, const string &p) {
        int m = s.size();
        int n = p.size();

        vector<vector<bool>> dp(m + 1 , vector<bool> (n + 1 , false)); // Time -> O(m * n) , Space -> O(m * n)

        dp[0][0] = true;

        for (int j = 2 ; j <= n ; j++) // Time -> O(n)
        {
            if (p[j - 1] == '*') dp[0][j] = dp[0][j - 2];
        }

        for (int i = 1 ; i <= m ; i++) // Time -> O(m * n)
        {
            for (int j = 1 ; j <= n ; j++)
            {
                if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) dp[i][j] = dp[i - 1][j - 1];
                else if (p[j - 1] == '*')
                {
                    dp[i][j] = dp[i][j - 2];

                    if (p[j - 2] == '.' || p[j - 2] == s[i - 1])
                    {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
                else dp[i][j] = false;
            }
        }

        return dp[m][n];
    }

    // Time complexity is O(m * n)
    // Space complexity is O(m * n)
};