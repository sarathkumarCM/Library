#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n=nums.size();
        int canReach=n-1;
        for(int i=n-1;i>=0;i--){
            if(nums[i]+i>=canReach){
                canReach=i;
            }
        }
        return (canReach==0)?true:false;
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
    cout<<s.canJump(inp);

}

//Best
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int mx = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (mx < i) {
                return false;
            }
            mx = max(mx, i + nums[i]);
        }
        return true;
    }
};

