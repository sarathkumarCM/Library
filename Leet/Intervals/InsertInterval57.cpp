#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bitset<10005> bts; 
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int sz=intervals.size();
        if(sz==0){
            return {newInterval};
        }
        vector<vector<int>> res;
        int curMax=-1,curMin=-1;
        for(int i=0;i<sz;i++){
                if(curMin==-1 && newInterval[0]<intervals[i][0]){
                    curMin=newInterval[0];
                }
                else if(curMin==-1 && newInterval[0]<=intervals[i][1]){
                    curMin=intervals[i][0];
                }
                if(curMin!=-1 && curMin!=INT_MAX){
                    if(newInterval[1]<=intervals[i][0]){
                        curMax=newInterval[1];
                        if(newInterval[1]==intervals[i][0]){
                            curMax=intervals[i][1];
                        }
                    }
                    else if(newInterval[1]<=intervals[i][1]){
                        curMax=intervals[i][1];
                    }
                }
                if(curMin!=INT_MAX && curMin!=-1 && curMax!=-1){
                    res.push_back({curMin,curMax});
                    curMax=INT_MAX;
                    curMin=INT_MAX;
                    if(res.back()[1] ==intervals[i][1] ||res.back()[0]==intervals[i][0]){
                        continue;
                    }
                }

                if((curMin==-1 && curMax==-1) || curMin==INT_MAX){
                    res.push_back({intervals[i][0],intervals[i][1]});
                }
                
        }
        if(curMin==-1){
            res.push_back(newInterval);
        }else if(curMax==-1){
            curMax=newInterval[1];
            res.push_back({curMin,curMax});
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
    vector<int> newInt(2);
    cin>>newInt[0]>>newInt[1];
    Solution s;
    auto res=s.insert(inp,newInt);
    for(auto &it:res){
        cout<<it[0]<<" "<<it[1]<<" ";
        cout<<endl;
    }
}

//best
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector <vector<int>> merged;

        int l = intervals.size();
        int i = 0;
        
        while(i < l && intervals[i][1] < newInterval[0]) {
            merged.push_back(intervals[i++]);
        }

        while(i < l && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0] , intervals[i][0]);
            newInterval[1] = max(newInterval[1] , intervals[i][1]);
            i++;
        }

        merged.push_back(newInterval);
        
        while(i<l) {
            merged.push_back(intervals[i++]);
        }

        return merged;
    }
};

//another approach
vector<vector<int>> insert(std::vector<std::vector<int>>& intervals,
                               std::vector<int> const& newInterval) {
        auto const it = std::ranges::upper_bound(intervals, newInterval);

        auto result = std::vector<std::vector<int>>{std::ranges::begin(intervals), it};
        // also
        auto const it = std::ranges::upper_bound(intervals, newInterval,
            [](auto const& left, auto const& right) -> bool {
                return left[0] < right[0];
            });

        if (!std::ranges::empty(result) && newInterval[0] <= result.back()[1]) {
            auto& interval = result.back();

            interval[0] = std::min(newInterval[0], interval[0]);
            interval[1] = std::max(newInterval[1], interval[1]);
        } else {
            result.push_back(newInterval);
        }

        for (auto const& interval : intervals | std::views::drop(result.size() - 1)) {
            if (result.back()[1] < interval[0]) {
                result.push_back(interval);
            } else {
                result.back()[1] = std::max(result.back()[1], interval[1]);
            }
        }

        return result;
    }
