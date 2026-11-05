#include<bits/stdc++.h>

using namespace  std;


class Solution {
public:
    int get_bit_width_log(int n) {
        // Logarithm is undefined for 0 or negative numbers
        if (n <= 0) {
            return 0; 
        }

        return std::floor(std::log2(n)) + 1;
    }
    vector<int> countBits(int n) {
        int count=0;
        vector<int> res;
        while(n>0){
            int x=__bit_width(n)-1;
            count+= x<<(x-1);
            n-=1<<x;
            count+=n+1;
        }
        
        return res;
    }
};

int main(){
    int n;
    cin>>n;
    Solution s;
    auto res=s.countBits(n);
    for(auto &it:res)cout<<it;
}

//OKOK
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res(n+1, 0);
        for(int i=1; i<=n; ++i){
            int num = i;
            while(num){
                res[i]++;
                num = num & num-1;
            }
        }

        return res;
    }
};

//Best
class Solution {
public:
    vector<int> countBits(int n) {

        vector<int> dp(n+1);

        dp[0]=0;

        for(int i=1;i<=n;i++){

            dp[i]=
                dp[i/2] + i%2;
        }

        return dp;
    }
};

class Solution {
public:
    vector<int> countBits(int n) {

        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; i++) {

            dp[i] = dp[i >> 1] + (i & 1);
        }

        return dp;
    }
};