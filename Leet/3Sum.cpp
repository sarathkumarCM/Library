#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int sz=nums.size();
        vector<vector<int>> res;
        unordered_map<int,int> nm;
        sort(nums.begin(),nums.end());
        for(int i=0;i<sz;i++){
            nm[nums[i]]=i;
        }
        for(int i=0;i<sz-1;i++){
            int target=-nums[i];
            int j=i+1;
            while(j<sz){
                int tt=target-nums[j];
                if(tt>nums[sz-1]||tt<nums[0]){
                    break;
                }
                if(nm[tt]&& nm[tt]!=i &&nm[tt]!=j){
                    //found=-- insert
                    vector<int> t(3);
                    t[0]=nums[i];t[1]=nums[j];t[2]=tt;
                    sort(t.begin(),t.end());
                    stringstream ss;
                    ss<<t[0]<<t[1]<<t[2];
                    string tmp=ss.str();
                    cerr<<tmp<<endl;
                    bool f=false;
                    for(auto it:res){
                        if(it[0]==t[0]&&it[1]==t[1]&&it[2]==t[2]){
                            f=true;
                            break;
                        }
                    }
                    if(!f)
                        res.push_back(t);

                }
                j++;
            }
        }
        return res;
           
    }
    vector<vector<int>> threeSum(vector<int>& nums,int n) {
        int sz=nums.size();
        set<vector<int>> resSet;
        unordered_map<int,int> nm,nm2;
        vector<int> nums2;

        for(int i=0;i<sz;i++){
            nm2[nums[i]]++;
        }
        for(auto val: nm2){
            if(val.second>3){
                val.second=3;
            }
            for(int j=0;j<val.second;j++){
                nums2.push_back(val.first);
            }
        }
        sz=nums2.size();
        sort(nums2.begin(),nums2.end());
        for(int i=0;i<sz;i++){
            nm[nums2[i]]=i;
        }
        for(int i=0;i<sz-1;i++){
            int target=-nums2[i];
            int j=i+1;
            while(j<sz){
                int tt=target-nums2[j];
                if(tt>nums2[sz-1]||tt<nums2[0]){
                    j++;
                    continue;
                }
                if(nm[tt]&& nm[tt]!=i &&nm[tt]!=j){
                    //found=-- insert
                    vector<int> t(3);
                    t[0]=nums2[i];t[1]=nums2[j];t[2]=tt;
                    sort(t.begin(),t.end());
                    resSet.insert(t);

                }
                j++;
            }
        }
        vector<vector<int>> res(resSet.begin(),resSet.end());
        return res;
           
    }
    //best
    vector<vector<int>> threeSum(vector<int>& nums, int k,int l) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) break;
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int l = i + 1, r = nums.size() - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum > 0) {
                    r--;
                } else if (sum < 0) {
                    l++;
                } else {
                    res.push_back({nums[i], nums[l], nums[r]});
                    l++;
                    r--;
                    while (l < r && nums[l] == nums[l - 1]) {
                        l++;
                    }
                }
            }
        }
        return res;
    }
};

int main(){
    int n;
    cin>>n;
    vector<int> ns(n);
    for(auto &it:ns){
        cin>>it;
    }
    vector<vector<int>> res;
    Solution s;
    res=s.threeSum(ns,0);
    for(auto it:res){
        for(auto it2: it){
            cout<<it2<<" ";
        }
        cout<<endl;
    }

}