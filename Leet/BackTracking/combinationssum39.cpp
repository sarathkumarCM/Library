#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void cb(int i, vector<int> &candidates, int target, vector<int> &cset, vector<vector<int>> &res, int sm){
        
        //int sm=accumulate(cset.begin(),cset.end(),0);
        if(sm==target){
            vector<int> tmp=cset;
            res.push_back(tmp);
            return;
        }
        else if(sm>target){
            return;
        }
        int n=candidates.size();
        if(i>=n){
            return;
        }
        //int j=i;
        for(int j=i;j<n;j++){
            cset.push_back(candidates[j]);
            sm+=candidates[j];
            cb(j,candidates,target,cset,res,sm);
            cset.pop_back();
            sm-=candidates[j];
        }
        return;
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        auto new_end=remove_if(candidates.begin(),candidates.end(),[&](int i){ return i>target;});
        candidates.erase(new_end,candidates.end());
        vector<vector<int>> res;
        vector<int> cSet;
        cb(0,candidates,target,cSet, res,0);
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
    vector<vector<int>> ans=s.combinationSum(inp,k);
    for(auto &it:ans){
        cout<<"[";
        for(auto &it2: it){
            cout<<","<<it2;
        }
        cout<<"]";
    }
}

class Solution2 {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end()); // Sort enables early break
        vector<vector<int>> result;
        vector<int> current;
        backtrack(candidates, target, 0, current, result);
        return result;
    }

private:
    // DFS backtracking: at each step choose a candidate >= candidates[start]
    void backtrack(vector<int>& candidates, int remaining, int start,
                   vector<int>& current, vector<vector<int>>& result) {
        if (remaining == 0) {
            result.push_back(current);  // Valid combination found
            return;
        }
        for (int i = start; i < (int)candidates.size(); i++) {
            // Since array is sorted, exceeding remaining means all
            // subsequent candidates also exceed it — prune early
            if (candidates[i] > remaining) break;

            current.push_back(candidates[i]);   // Choose candidate
            // Pass i (not i+1) to allow reusing the same candidate
            backtrack(candidates, remaining - candidates[i], i, current, result);
            current.pop_back();  // Un-choose (backtrack)
        }
    }
};
