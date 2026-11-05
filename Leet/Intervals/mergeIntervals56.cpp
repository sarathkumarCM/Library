#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int sz=intervals.size();
        if(intervals.size()<=1)
            return intervals;
        ranges::sort(intervals);
        vector<vector<int>> res;
        res.push_back(intervals[0]);
        for(int i=1;i<sz;i++){
            if(res.back()[1]<intervals[i][0]){
                res.push_back(intervals[i]);
            }else{
                res.back()[1]=max(res.back()[1],intervals[i][1]);
            }
        }
        
        return res;
    }
};


int main(){
    int n;
    cin>>n;
    vector<vector<int>> inp(n,vector<int>(2));
    for(auto &it:inp){
        cin>>it[0]>>it[1];
    }
    Solution s;s
    auto res=s.merge(inp);
    for(auto &it:res){
        cout<<it[0]<<" "<<it[1]<<" ";
        cout<<endl;
    }

}

//best
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals)
    {
        std::sort(intervals.begin(), intervals.end(), [](const vector<int>& lhs, const vector<int>& rhs)
        {
            return tie(lhs[0], lhs[1]) < tie(rhs[0], rhs[1]);
        });

        vector<vector<int>> merged;
        if (!intervals.empty())
            merged.push_back(intervals.front());

        for (int i = 1; i < intervals.size(); ++i)
        {
            if (doOverlap(merged.back(), intervals[i]))
            {
                merged.back()[1] = max(merged.back()[1], intervals[i][1]);
            }
            else
                merged.push_back(intervals[i]);
        }

        return merged;
    }

private:
    bool doOverlap(const vector<int>& lhs, const vector<int>& rhs) const
    {
        int minLhs = lhs[0];
        int maxLhs = lhs[1];
        int minRhs = rhs[0];
        int maxRhs = rhs[0];

        if (minLhs <= minRhs && minRhs <= maxLhs) return true;

        return false;


    }
};