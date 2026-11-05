#include<bits/stdc++.h>

using namespace std;

class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int p1=0,p2=0;
            int sz=prices.size();
            int max_ret=INT_MIN;
            int minVal=prices[0];
            for(int i=1;i<sz-1;i++){
                max_ret=max(max_ret,prices[i]-minVal);
                minVal=min(minVal,prices[i]);
            }
            if(max_ret<=0)
                return 0;
            else
                return max_ret;
        }
    };

int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(auto &it:a){
        cin>>it;
    }
    Solution s;
    cout<<s.maxProfit(a)<<endl;
}