#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /* not working
    bool dfs(int i,int j,string s1,string s2, string tmp,string target){
        if(tmp==target) return true;
        bool res=false;
        if(i<s1.size()){
            string s1t=tmp+s1[i];
            res=res||dfs(i+1,j,s1,s2,s1t,target);
        }
        if(j<s2.size()){
            string s2t=tmp+s2[j];
            res=res||dfs(i,j+1,s1,s2,s2t,target);
        }
        return res;
    }
    bool isInterleaveDfs(string s1, string s2, string s3) {
        if(s3.size()!=(s1.size()+s2.size()))return false;
        return dfs(0,0,s1,s2,"",s3);
    }
    //Memory limit exceeded;
    bool Memo(int i,int j,string s1,string s2, string tmp,string target, vector<vector<unordered_map<string,bool>>> &memo){
        if(tmp==target) return true;
        bool res=false;
        if(i<s1.size()){
            string s1t=tmp+s1[i];
            if(memo[i+1][j][s1t]) return memo[i+1][j][s1t];
            res=res||Memo(i+1,j,s1,s2,s1t,target,memo);
        }
        if(j<s2.size()){
            string s2t=tmp+s2[j];
            if(memo[i+1][j][s2t]) return memo[i+1][j][s2t];
            res=res||Memo(i,j+1,s1,s2,s2t,target,memo);
        }
        memo[i][j][tmp]=res;
        return res;
    }
    bool isInterleaveMemo(string s1, string s2, string s3) {
        if(s3.size()!=(s1.size()+s2.size()))return false;
        vector<vector<unordered_map<string,bool>>> memo(s1.size()+5,vector<unordered_map<string,bool>>(s2.size()+5));
        return Memo(0,0,s1,s2,"",s3,memo);
    }
    */
    // working...
    bool dfs2(int i,int j,string &s1,string &s2,string &target){
        if(i+j==target.size()) return true;
        bool res=false;
        if(i<s1.size() && i+j< target.size() && s1[i]==target[i+j]){
            res=res||dfs2(i+1,j,s1,s2,target);
        }
        if(j<s2.size()&& i+j<target.size() && s2[j]==target[i+j]){
            res=res||dfs2(i,j+1,s1,s2,target);
        }
        return res;
    }

    bool isInterleaveDfs(string s1, string s2, string s3) {
        if(s3.size()!=(s1.size()+s2.size()))return false;
        return dfs2(0,0,s1,s2,s3);
    }

    bool Memo(int i,int j,string s1,string s2,string target,vector<vector<int>> &dp){
        if(i+j==target.size()) return true;
        bool res=false;
        if(dp[i][j]!=-1)return dp[i][j];
        if(i<s1.size() && i+j< target.size() && s1[i]==target[i+j]){
            res=res||Memo(i+1,j,s1,s2,target,dp);
        }
        if(j<s2.size()&& i+j<target.size() && s2[j]==target[i+j]){
            res=res||Memo(i,j+1,s1,s2,target,dp);
        }
        dp[i][j]=res;
        return res;
    }

    bool isInterleaveMemo(string s1, string s2, string s3) {
        if(s3.size()!=(s1.size()+s2.size()))return false;
        vector<vector<int>> dp(s1.size()+5,vector<int>(s2.size()+5,-1));
        return Memo(0,0,s1,s2,s3,dp);
    }

     bool isInterleave(string s1, string s2, string s3) {
        int m=s1.size(),n=s2.size(),mn=s3.size();
        if(mn!=(m+n))return false;
        vector<vector<bool>> dp(m+1,vector<bool>(n+1,0));
        dp[m][n]=true;
        for(int i=m-1;i>=0;i--){
            dp[i][n]=(s1[i]==s3[i+n]) && dp[i+1][n];
            
        }
        for(int i=n-1;i>=0;i--){
            dp[m][i]=(s2[i]==s3[i+m]) && dp[m][i+1];
        }
        for(int i=m-1;i>=0;i--){
            for(int j=n-1;j>=0;j--){
                bool res=false;
                if(s1[i]==s3[i+j]){
                    res=res||dp[i+1][j];
                }
                if(s2[j]==s3[i+j]){
                    res=res||dp[i][j+1];
                }
                dp[i][j]=res;
            }
        }

        
        return dp[0][0];
    }
};

int main(){
    string s1,s2,t;
    cin>>s1>>s2>>t;
    Solution s;
    cout<<s.isInterleave(s1,s2,t);
}

//best
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int  m = s1.length(), n = s2.length(), o = s3.length();
        if(m+n!=o) return false;
        vector<vector<bool>> dp(m+1,vector<bool>(n+1,true));
        //Base Case
        for(int i = 0 ; i<m ; i++) dp[i+1][0]=dp[i][0] && s3[i]==s1[i];
        for(int j = 0 ; j<n ; j++) dp[0][j+1]=dp[0][j] && s3[j]==s2[j];
        //DP
        for(int i= 0; i<m; i++){
            for(int j= 0 ; j<n ; j++){
                dp[i+1][j+1] = (dp[i][j+1] && (s3[i+j+1] == s1[i])) || (dp[i+1][j] && (s3[i+j+1] == s2[j]));
            }
        }
        return dp[m][n];
    }
};

//another memo
class Solution {
    vector<vector<int>> dp;

public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.length(), n = s2.length();
        if (m + n != s3.length()) return false;
        dp = vector<vector<int>>(m + 1, vector<int>(n + 1, -1));
        return dfs(0, 0, 0, s1, s2, s3);
    }

    bool dfs(int i, int j, int k, string& s1, string& s2, string& s3) {
        if (k == s3.length()) {
            return (i == s1.length()) && (j == s2.length());
        }
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        bool res = false;
        if (i < s1.length() && s1[i] == s3[k]) {
            res = dfs(i + 1, j, k + 1, s1, s2, s3);
        }
        if (!res && j < s2.length() && s2[j] == s3[k]) {
            res = dfs(i, j + 1, k + 1, s1, s2, s3);
        }

        dp[i][j] = res;
        return res;
    }
};

//another bottom up
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.length(), n = s2.length();
        if (m + n != s3.length()) {
            return false;
        }

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[m][n] = true;

        for (int i = m; i >= 0; i--) {
            for (int j = n; j >= 0; j--) {
                if (i < m && s1[i] == s3[i + j] && dp[i + 1][j]) {
                    dp[i][j] = true;
                }
                if (j < n && s2[j] == s3[i + j] && dp[i][j + 1]) {
                    dp[i][j] = true;
                }
            }
        }
        return dp[0][0];
    }
};