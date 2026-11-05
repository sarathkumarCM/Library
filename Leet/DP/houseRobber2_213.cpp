#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int helper(vector<int> &nums){
        int n=nums.size();
        int prev2=0;
        int prev1=nums[0];
        for(int i=1;i<n;i++){
            int skip=prev1;
            int incl=prev2+nums[i];
            int ans=max(skip,incl);
            prev2=prev1;
            prev1=ans;
        }
        return prev1;
    }
    int rob(vector<int>& nums) {
        if(nums.size()==1){
            return nums[0];
        }
        else if(nums.size()==2){
            return max(nums[0],nums[1]);
        }
        int sz=nums.size();
        vector<int> num2;
        vector<int> nums3;
        for(int i=1;i<sz;i++){
            num2.push_back(nums[i]);
        }

        for(int i=0;i<sz-1;i++){
            nums3.push_back(nums[i]);
        }

        return max(helper(num2),helper(nums3));
    }
};

int main(){
    int n;
    cin>>n;
    vector<int> cost(n);
    for(auto &it:cost){
        cin>>it;
    }
    Solution s;
    cout<<s.rob(cost);
}

//best
class Solution2 {
public:
    int rob(vector<int>& nums) {
        if(nums.size()==1) return nums[0];
        if(nums.size()==2) return max(nums[0], nums[1]);
        return max(doit(nums, 0, nums.size() - 2),
                   doit(nums, 1, nums.size() - 1));
    }
    int doit(vector<int>& nums, int l, int r) {
        int prev = 0, cur = 0;
        prev = nums[l];
        cur = max(nums[l], nums[l + 1]);
        for (int i = l + 2; i <= r; i++) {
            int temp = max(nums[i] + prev, cur);
            prev = cur;
            cur = temp;
        }
        return cur;
    }
};