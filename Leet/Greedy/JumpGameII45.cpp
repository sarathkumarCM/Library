#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int n=nums.size();
        int curMinJ=0,mx=0,curMax=0;
        for(int i=0;i<n-1;i++){
            mx=max(mx,i+nums[i]);
            if(curMax==i){
                curMinJ++;
                curMax=mx;
            }
            
        }
        return curMinJ;
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
    cout<<s.jump(inp);

}

//best
class Solution {
public:
    int jump(vector<int>& nums) {
        int n=nums.size();
        int jumps=0;
        int l=0;
        int r=0;
        while(r<n-1){
            int farth=INT_MIN;
            for(int i=l;i<=r;i++){
                farth=max(farth,i+nums[i]);
            }
            l=r+1;
            r=farth;
            jumps++;
        }
        return jumps;
    }
};