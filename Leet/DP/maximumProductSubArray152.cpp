#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProductNotWorking(vector<int>& nums) {
        int n=nums.size();
        vector<int> dp(nums.size()+1,INT_MIN);
        for(int i=0;i<n;i++){
            if(i==0){
                dp[i]=max(INT_MIN,nums[i]);
                 //cerr<<"current max 1: "<<dp[i]<<endl;
            }else{
                dp[i]=max(nums[i],dp[i-1]*nums[i]);
                //cerr<<"current max: "<<dp[i]<<endl;
            }
        }
        auto it=max_element(dp.begin(),dp.end());
        return *it;
    }
    int maxProductBrute(vector<int>& nums) {
        int n=nums.size();
        vector<int> dp(nums.size()+1,INT_MIN);
        int mxp=INT_MIN;
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                if(i==j){
                    dp[j]=nums[j];
                }else{
                    dp[j]=dp[j-1]*nums[j];
                }
                mxp=max(dp[j],mxp);
            }
        }
        
        return mxp;
    }
    int dfs(int i, vector<int> &nums){
        if(i==nums.size()-1){
            return nums[nums.size()-1];
        }
        int res=dfs(i+1,nums);
        
        res=max(res*nums[i],res);
        cerr<<"Cur Res for i: "<<i<<" is: "<<res<<endl;
        return res;
    }
     int dfsMemo(int i, vector<int> &nums,vector<int> &dp){
        if(i==nums.size()-1){
            return nums[nums.size()-1];
        }
        if(dp[i]!=INT_MIN){
            return dp[i];
        }
        dp[i]=dfs(i+1,nums);
        dp[i]=max(dp[i],dp[i]*nums[i]);
        return dp[i];
    }
    int maxProductRecMemo(vector<int>& nums) {
        
        return dfs(0,nums);
        //vector<int> dp(nums.size()+1,INT_MIN);
        //return dfsMemo(0,nums,dp);
        //return mxp;
    }

    //Best mine

    int maxProduct(vector<int>& nums) {
        int n=nums.size();
        vector<pair<int,int>> dp(nums.size()+1,make_pair(INT_MAX,INT_MIN));
        for(int i=0;i<n;i++){
            if(i==0){
                dp[i].second=nums[i];
                dp[i].first=nums[i];
            }else{
                dp[i].second=max({nums[i],dp[i-1].second*nums[i],dp[i-1].first*nums[i]});
                dp[i].first=min({nums[i],dp[i-1].first*nums[i],dp[i-1].second*nums[i]});
            }
        }
        int mx=INT_MIN;
        for(int i=0;i<n;i++){
            mx=max({mx,dp[i].first,dp[i].second});
        }
        return mx;
    }



};

int main(){
    int n;
    cin>>n;
    vector<int> inp(n);
    for(auto &it: inp){
        cin>>it;
    }
    Solution s;
    cout<<s.maxProduct(inp);
}

//best sol
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxPos = 0, minNeg = 0, ans = INT_MIN;
        for (const auto& k : nums) {
            ans = max(ans, k);
            if (k == 0) {
                maxPos = minNeg = 0;
            } else if (k > 0) {
                maxPos = maxPos == 0 ? k : maxPos * k;
                minNeg = minNeg == 0 ? 0 : minNeg * k;
            } else {
                int tmpMaxPos = maxPos, tmpMinNeg = minNeg;
                maxPos = tmpMinNeg == 0 ? 0 : tmpMinNeg * k;
                minNeg = tmpMaxPos == 0 ? k : tmpMaxPos * k;
            }
            if (maxPos != 0)
                ans = max(ans, maxPos);
            if (minNeg != 0)
                ans = max(ans, minNeg);
        }
        return ans;
    }
};