#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    int dfs4(vector<int>& nums,int i, int prevIndex){

        if(i==nums.size()) return 0;
        int notTake=dfs4(nums,i+1,prevIndex);
        int taken=0;
        if(prevIndex==-1|| nums[i]>nums[prevIndex]){
            taken=(1+dfs4(nums,i+1,i));
        }
        return max(taken,notTake);
    }

    
    int lengthOfLIS2(vector<int>& nums) {
        int n=nums.size();
        if(n==1)
            return 1;
        return dfs4(nums,0,-1);
    }

    int lengthOfLIS(vector<int>& nums) {
        int n=nums.size();
        if(n==1)
            return 1;
        vector<int> dp(n,1);
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[j]<nums[i]){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }
        }
        return *max_element(dp.begin(),dp.end());
    }
};

int main(){
    int n;
    cin>>n;
    vector<int> inp(n);
    for(auto &it:inp){
        cin>>it;
    }
    Solution s;
    cout<<s.lengthOfLIS(inp);
}

//best
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> res;

        for (int n : nums) {
            if (res.empty() || res.back() < n) {
                res.push_back(n);
            } else {
                int idx = binarySearch(res, n);
                res[idx] = n;
            }
        }

        return res.size();        
    }

private:
    int binarySearch(const vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }    
};

//best 2
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int>tails; 
        
        for (int i=0; i<n; i++) {
            int ind = lower_bound(tails.begin(), tails.end(), nums[i]) - tails.begin();
            if (ind == tails.size()) {
                tails.push_back(nums[i]);
            } else {
                tails[ind] = nums[i];
            }
        }
        return tails.size();
    }
};
