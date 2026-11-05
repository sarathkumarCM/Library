#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> result;
        unordered_map<int,int> interim;
        for(auto &num:nums){
            interim[num]++;
        }
        vector<pair<int,int>> items;
        for(auto &num: interim){
            items.push_back({num.second,num.first});
        }

        sort(items.begin(),items.end(),greater<pair<int,int>>());
        for(int i=0;i<k;i++){
            result.push_back(items[i].second);
        }
        return result;
    }
};

int main(){
    Solution s;

    vector<int> av={1,1,1,2,2,3};
    auto a=s.topKFrequent(av,2);
    for(auto &it: a){
        cout<<it<<" ";
    }
    cout<<endl;
}
