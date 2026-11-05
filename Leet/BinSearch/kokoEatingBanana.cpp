#include<bits/stdc++.h>

using namespace std;

class Solution {
        int calcIfPossible(vector<int>& piles, int val){
            int tm=0;
            for(auto it: piles){
                //tm+=(it/val) + (it%val==0?0:1);
                tm+=(it+val-1)/val; //ceil better

            }
            return tm;
        }
    public:
        int minEatingSpeed(vector<int>& piles, int h) {
            int max=*max_element(piles.begin(),piles.end());
            int min=1;
            int res=max;
            while(min<max){
                int mid=(min+max)/2;
                int tmTaken=calcIfPossible(piles,mid);
                if(tmTaken>h){
                    min=mid+1;
                }else{
                    if(mid<res)
                            res=mid;
                    max=mid;
                }
            }
            return res;
        }
    };

int main(){
    int n,h;
    cin>>n;
    vector<int> inp(n);
    for(auto &it:inp){
        cin>>it;
    }
    cin>>h;
    Solution s;
    cout<<s.minEatingSpeed(inp,h);

}