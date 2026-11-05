#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int sz=nums.size();
        vector<int> pref(sz,1);

        for(int i=1;i<sz;i++){
            pref[i]=pref[i-1]*nums[i-1];
        }
        int right=1;
        for(int j=sz-2;j>=-1;j--){
            pref[j+1]=pref[j+1]*right;
            right*=nums[j+1];
        }
        return pref;
    }
};


int main(){
    Solution s;

    vector<int> inp={1,2,3,4};
    auto a=s.productExceptSelf(inp);
    for(auto &it: a){
        cout<<it<<" ";
        
        
    }
    cout<<endl;
}
