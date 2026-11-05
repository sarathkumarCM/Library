#include<bits/stdc++.h>
using namespace std;
//n!
class Solution {
public:

    vector<vector<int>> perm(int i, vector<int> &nums){
        if(i==nums.size())
            return{{}};
        vector<vector<int>> res;
        vector<vector<int>> perms=perm(i+1,nums);
        for(auto &it: perms){
            for(int j=0;j<=it.size();j++){
                //list<int> tperm(it.begin(),it.end()); -- best
                //auto tb=tperm.begin();
                //advance(tb,j);
                //tperm.insert(tb,nums[i]);
                vector<int> meh;
                for(int k=0;k<it.size();k++){
                    if(j==k)
                        meh.push_back(nums[i]);
                    meh.push_back(it[k]);
                }
                if(j==it.size()){
                    meh.push_back(nums[i]);
                }
                //vector<int> tt (tperm.begin(),tperm.end());
                res.push_back(meh);
            }

        }
        return res;
        

    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> perms;
        vector<int> cperm;
        perms=perm(0,nums);
        return perms;
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
    vector<vector<int>> res=s.permute(inp);
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

//best
class Solution2 {
private:
    void bt(int idx, vector<int>& nums, vector<vector<int>>&rv) {
        if (idx == nums.size()) {
            rv.push_back(nums);
        }

        for (int i = idx; i < nums.size(); ++i) {
            swap(nums[idx], nums[i]);
            bt(idx + 1, nums, rv);
            swap(nums[idx], nums[i]);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> rv;
        bt(0, nums, rv);
        return rv;
    }
};