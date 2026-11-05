#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isValid(string s){
        if(s.size()>2 || s.size()==0){
            return false;
        }
        if(s[0]=='0'){
            return false;
        }
        int val=stoi(s);
        if(val<1 || val>26)
            return false;

        return true;

    }
    int numDecodingsOld(string s) {
        int n=s.size();
        if(n>1 && s[n-1]=='0'){
            int c=s[n-2]-'0';
            if(c>2)
                return 0;
        }
        vector<int> dp(n+1,0);
        dp[0]=1; // all ones; if there is a. 0 it would be a 0;
        for(int i=0;i<n;i++){
            if(s[i]=='0'){
                dp[0]=0;
            }
        }
        for(int i=0;i<n-1;i++){
            string s1=s.substr(i,2);
            if(s1=="00"){
                return 0;
            }
            int val=0;
            if(isValid(s1)){
                cerr<<" valid: "<<s1<<endl;
                val=1;
            }
            dp[i+1]=max(dp[i],dp[i]+val);
            cerr<<"i th elem: "<<dp[i]<<endl;
        }
        return dp[n-1];

    }
    int numDecodings(string s) {
        int n=s.size();
        vector<int> dp(n+2);
        dp[n]=1;dp[n+1]=1;
        for(int i=n-1;i>=0;i--){
            if(s[i]=='0'){
                dp[i]=0;
                continue;
            }
            dp[i]=dp[i+1];
            if((i+1)<s.size()){
                string s1=s.substr(i,2);
                if (isValid(s1)) {
                    dp[i] += dp[i+2];
                }
            }
            //cerr<<"DP["<<i<<"] : "<<dp[i]<<endl;
        }
        return dp[0];
    }
    
    int dfs(int i, string s){
        if(i>=s.size())
            return 1;
        if(s[i]=='0')
            return 0;
        int res=dfs(i+1,s);
        if((i+1)<s.size()){
            string s1=s.substr(i,2);
            if (isValid(s1)) {
                res += dfs(i+2, s);
            }
        }
        return res;
    }
    int solve(string &s, int i) {
        // Base case: reached end → valid decoding
        if (i == s.size()) return 1;

        // If current digit is '0', invalid
        if (s[i] == '0') return 0;

        // Take single digit
        int ways = solve(s, i + 1);

        // Take two digits (if valid: 10–26)
        if (i + 1 < s.size()) {
            int num = (s[i] - '0') * 10 + (s[i + 1] - '0');
            if (num >= 10 && num <= 26) {
                ways += solve(s, i + 2);
            }
        }

        return ways;
    }
    int numDecodingsIssue2(string s) {
        int n=s.size();
        int ans=0;
       
        return dfs(0,s);
        //return solve(s,0);
    }
    int dfs2(int i, string s,vector<int> &dp){
        if(i>=s.size())
            return 1;
        if(s[i]=='0')
            return 0;
        if(dp[i]!=-1)
            return dp[i];
        int res=dfs(i+1,s);
        if((i+1)<s.size()){
            string s1=s.substr(i,2);
            if (isValid(s1)) {
                res += dfs(i+2, s);
            }
        }
        dp[i]=res;
        return res;
    }
    int numDecodingsIssueMemo(string s) {
        int n=s.size();
        int ans=0;
        vector<int> dp(n+2,-1);
        return dfs2(0,s,dp);
        //return solve(s,0);
    }
    int numDecodingsmeh(string s) {
        int n = s.size();
        if (!n || s[0] == '0') return 0;
        int prev2 =0, prev1 = 1;
        int cur=0;
        for (int i = 2; i <= n; i++) {
            if (s[i-1] != '0') cur += prev1;
            int x = (s[i-2]-'0')*10 + (s[i-1]-'0');
            if (x >= 10 && x <= 26) cur += prev2;

            prev2=prev1;
            prev1=cur;
            cur=0;
        }
        return cur;
}
};

int main(){
    string ss;
    cin>>ss;
    Solution s;
    cout<<s.numDecodingsmeh(ss);
}

//best
int numDecodings(string s) {
        int n = s.size();
        if (!n || s[0] == '0') return 0;
        vector<int> dp(n+1,0);
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (s[i-1] != '0') dp[i] += dp[i-1];
            int x = (s[i-2]-'0')*10 + (s[i-1]-'0');
            if (x >= 10 && x <= 26) dp[i] += dp[i-2];
        }
        return dp[n];
}


//best 2
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        if (s[0] == '0') return 0;

        int prev2 = 1; // dp[i-2]
        int prev1 = 1; // dp[i-1]

        for (int i = 1; i < n; i++) {
            int curr = 0;

            // single digit
            if (s[i] != '0') {
                curr += prev1;
            }

            // two digit
            int two = (s[i-1] - '0') * 10 + (s[i] - '0');
            if (two >= 10 && two <= 26) {
                curr += prev2;
            }

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};
