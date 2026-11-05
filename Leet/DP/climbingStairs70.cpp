#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n+1,0);
        dp[0]=0,dp[1]=1;
        if(n>1) dp[2]=2;
        int i=3;
        while(i<n+1){

            dp[i]=dp[i-1]+dp[i-2];
            i++;
        }
        return dp[n];
    }
};

int main(){
    int n;
    cin>>n;
    Solution s;
    cout<<s.climbStairs(n);
}

//best
class Solution {
public:
    int climbStairs(int n) {
        if(n <= 2) return n;
        int a = 1, b = 2;
        for(int i = 3; i <= n; i++) {
            int c = a + b;
            a = b;
            b = c;
        }
        return b;
    }
};