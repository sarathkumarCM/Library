#include<bits/stdc++.h>
using namespace std;

//2^n

class Solution {
public:

    void gen(int idx,vector<int>& nums,vector<vector<int>>&ans,vector<int>&temp) //also good
    {
        ans.push_back(temp);
        for(int i=idx;i<nums.size();i++)
        {
            temp.push_back(nums[i]);
            gen(i+1,nums,ans,temp);
            temp.pop_back();
            while((i+1)<nums.size() && nums[i]==nums[i+1]){
                i++;
            }
        }
    }

    void sb(vector<int>& nums, int i,vector<vector<int>> &subsets,vector<int> &resSet){
        if(i==nums.size()){
            vector<int> newSet=resSet;
            subsets.push_back(newSet);
            return;
        }
        resSet.push_back(nums[i]);
        
        sb(nums,(i+1), subsets,resSet);
        resSet.pop_back();
        while((i+1)< nums.size() &&nums[i]==nums[i+1]){
            i++;
        }
        sb(nums,(i+1),subsets, resSet);
        return;
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> subsets;
        vector<int> cSet;
        sb(nums,0, subsets,cSet);
        return subsets;
    }
};

int main(){
    int n;
    cin>>n;
    vector<int> inp(n);
    for(auto &it: inp){
        cin>>it;
    }
    Solution s;
    vector<vector<int>> res=s.subsets(inp);
    cout<<"[";
    for(auto &it1:res){
        cout<<"[";
        for(auto &it2: it1){
            cout<<" "<<it2;
        }
        cout<<"],";
    }
    cout<<"]"<<endl;
}

