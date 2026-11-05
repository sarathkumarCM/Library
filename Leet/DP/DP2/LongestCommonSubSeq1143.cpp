#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m=text1.size(),n=text2.size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(text1[i]==text2[j]){
                    dp[i+1][j+1]=1+dp[i][j];
                }else{
                    dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j]);
                }
            }
        }
        return dp[m][n];
    }

    int longestCommonSubsequenceBest(string text1, string text2) {
        int m=text1.size(),n=text2.size();
        vector<int> dp(n+1,0);
        for(int i=0;i<m;i++){
            vector<int> cur(n+1,0);
            for(int j=0;j<n;j++){
                if(text1[i]==text2[j]){
                    cur[j+1]=1+dp[j];
                }else{
                    cur[j+1]=max(dp[j+1],cur[j]);
                }
            }
            dp=cur;
        }
        return dp[n];
    }

    int lcs(string s, string d,int i,int j, int m, int n){
        if(i>m-1 ||j>m-1) return 0;
        if(s[i]==d[j])
            return 1+lcs(s,d,i+1,j+1,m,n);
        return max(lcs(s,d,i+1,j,m,n),lcs(s,d,i, j+1,m,n));
    }

    //Memoize based on i & j;
    int lcsMemo(string s, string d,int i,int j, int m, int n,vector<vector<int>> &memo){
        if(i>m-1 ||j>m-1) return 0;
        if(memo[i][j]!=-1) return memo[i][j];
        if(s[i]==d[j]){
            memo[i][j]= 1+lcsMemo(s,d,i+1,j+1,m,n,memo);
            return memo[i][j];
        }
        memo[i][j]= max(lcsMemo(s,d,i+1,j,m,n,memo),lcsMemo(s,d,i, j+1,m,n,memo));
        return memo[i][j];
    }
};

int main(){
    string s1,s2;
    cin>>s1>>s2;
    Solution s;
    cout<<s.longestCommonSubsequenceBest(s1,s2);
    //Rev
    //cout<<s.lcs(s1,s2,0,0,s1.size(),s2.size());
    //Memop
    //vector<vector<int>> memo(s1.size(),vector<int>(s2.size(),-1));
    //cout<<s.lcsMemo(s1,s2,0,0,s1.size(),s2.size(),memo);

}

//Best
class Solution {
public:
    int longestCommonSubsequence(string a, string b) {
        // Ensure b is the shorter dimension for faster bitset ops (optional)
        if (b.size() > a.size()) swap(a, b);

        int n = (int)a.size();
        int m = (int)b.size();
        if (m == 0) return 0;

        // Number of 64-bit blocks
        int W = (m + 63) >> 6;

        // positions[ch][block] bit = 1 if b[pos]==ch
        static unsigned long long pos[26][8000]; 
        // 8000 blocks covers m up to 8000*64=512k, adjust if needed
        // For typical LC constraints (<=1000 or 3000) this is plenty.

        for (int c = 0; c < 26; ++c)
            for (int i = 0; i < W; ++i)
                pos[c][i] = 0;

        for (int j = 0; j < m; ++j) {
            int c = b[j] - 'a';
            pos[c][j >> 6] |= 1ULL << (j & 63);
        }

        // DP bitset
        vector<unsigned long long> D(W, 0ULL), X(W), Y(W);

        for (int i = 0; i < n; ++i) {
            unsigned long long carry = 1ULL; // corresponds to shifting and adding 1
            int c = a[i] - 'a';

            // X = pos[c] | D
            for (int k = 0; k < W; ++k) X[k] = pos[c][k] | D[k];

            // Y = (D << 1) | 1
            for (int k = 0; k < W; ++k) {
                unsigned long long newCarry = D[k] >> 63;
                Y[k] = (D[k] << 1) | carry;
                carry = newCarry;
            }

            // D = X & ~(X - Y)   (bit-parallel LCS transition)
            unsigned long long borrow = 0ULL;
            for (int k = 0; k < W; ++k) {
                unsigned long long x = X[k];
                unsigned long long y = Y[k];

                // compute x - y - borrow in unsigned arithmetic
                unsigned long long sub = x - y - borrow;
                borrow = (x < y + borrow) ? 1ULL : 0ULL;

                D[k] = x & ~sub;
            }
        }

        // popcount of D gives LCS length
        int ans = 0;
        for (int k = 0; k < W; ++k) ans += __builtin_popcountll(D[k]);
        return ans;
    }
};

//another DP
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<int> dp(text1.length(), 0);
        int longest = 0;

        for (char c: text2) {
            int curr_len = 0;
            for(int i = 0; i<dp.size(); i++) {
                if(curr_len < dp[i]) {
                    curr_len = dp[i];
                } else if (c == text1[i]){
                    dp[i] = curr_len +1;
                    longest = max(longest, curr_len+1);
                }
            }
        }
        return longest;
    }
};