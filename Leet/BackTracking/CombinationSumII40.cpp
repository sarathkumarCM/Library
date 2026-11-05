#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void cb(int i, vector<int> &candidates, int target, vector<int> &cset, vector<vector<int>> &res){
        
        int sm=accumulate(cset.begin(),cset.end(),0);
        if(sm==target){
            vector<int> tmp=cset;
            res.push_back(tmp);
            return;
        }
        else if(sm>target){
            return;
        }

        if(i>=candidates.size()){
            return;
        }
        cset.push_back(candidates[i]);
        cb(i+1,candidates,target,cset,res);
        cset.pop_back();
        while((i+1)< candidates.size() &&candidates[i]==candidates[i+1]){
            i++;
        }
        cb(i+1,candidates,target,cset,res);
        return;
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        auto new_end=remove_if(candidates.begin(),candidates.end(),[&](int i){ return i>target;});
        candidates.erase(new_end,candidates.end());
        sort(candidates.begin(),candidates.end());
        vector<vector<int>> res;
        vector<int> cSet;
        cb(0,candidates,target,cSet, res);
        return res;
    }
};

int main(){
    int n,k;
    cin>>n>>k;
    vector<int> inp(n);
    for(auto &it: inp){
        cin>>it;
    }
    Solution s;
    vector<vector<int>> ans=s.combinationSum2(inp,k);
    for(auto &it:ans){
        cout<<"[";
        for(auto &it2: it){
            cout<<","<<it2;
        }
        cout<<"]";
    }
}

//Best
class Solution2 {
public:
    void backtrack(vector<vector<int>>&res, vector<int>&curr, int ind, vector<int>& candidates, int target, int sum){
        int n = candidates.size();
        if (sum > target) return;
        if(sum == target){
            res.push_back(curr);
            return;
        }
        for(int i=ind; i<n; i++){
            if(i > ind && candidates[i] == candidates[i-1])continue;
            curr.push_back(candidates[i]);
            sum += candidates[i];
            backtrack(res, curr, i+1, candidates, target, sum);

            curr.pop_back();
            sum -= candidates[i];
        }        

        
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end()); 
        vector<vector<int>>res;
        vector<int>curr;
        int sum = 0;
        backtrack(res, curr, 0, candidates, target, 0);
        return res;
    }
};