#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int sz=height.size();
        int i=0,j=sz-1;
        int maxArea=0;
        while(i<j){
            int area=(j-i)*min(height[i],height[j]);
            maxArea=max(maxArea,area);
            if(height[i]>height[j])
                j--;
            else
                i++;
        }
        return maxArea;
    }
};

int main(){

    Solution s;
    int n;
    cin>>n;
    vector<int> k(n);
    for(auto &it:k){
        cin>>it;
    }
    auto ans=s.maxArea(k);
    cout<<ans<<endl;
}