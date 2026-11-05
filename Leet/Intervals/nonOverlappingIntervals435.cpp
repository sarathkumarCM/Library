#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int sz=intervals.size();
        if(intervals.size()<=1)
            return 0;
        sort(intervals.begin(),intervals.end(),[](vector<int> &lhs,vector<int> &rhs){
            return lhs[1]<rhs[1];
        });
        vector<vector<int>> res;
        int cnt=0;
        res.push_back(intervals[0]);
        for(int i=1;i<sz;i++){
            if(res.back()[1]<=intervals[i][0]){
                res.push_back(intervals[i]);
            }else{
                cerr<<"overlap at"<<intervals[i][0]<<" "<<intervals[i][1]<<endl;
                //res.back()[1]=max(res.back()[1],intervals[i][1]);
                cnt++;
            }
        }
        
        return cnt;
    }
};


int main(){
    int n;
    cin>>n;
    vector<vector<int>> inp(n,vector<int>(2));
    for(auto &it:inp){
        cin>>it[0]>>it[1];
    }
    Solution s;
    cout<<s.eraseOverlapIntervals(inp)<<endl;

}

//best
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {

        int mi = intervals[0][0], mx = intervals[0][1];
        for(vector<int> &interval: intervals){
            mi = min(mi, interval[0]);
            mx = max(mx, interval[1]);
        }
        mi = abs(mi);
        vector<int> v(mx+mi+1, INT_MAX);
        int nonOverlappingInt = 0;
        for(vector<int> &interval: intervals){
            v[interval[0] + mi] = min(v[interval[0] + mi], interval[1] + mi);
        }
        int prev = INT_MAX;
        for(int i = 0; i < v.size(); i++){
            if(prev == i){
                nonOverlappingInt++;
                prev = INT_MAX;
            }
            if(v[i] < prev){
                prev = v[i];
            }
        }
        return intervals.size() - nonOverlappingInt;
    }
};


//another
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& interval1, const vector<int>& interval2){
            return interval1[0] < interval2[0];
        });

        int intervalsToRemove = 0;
        int prevInterval = 0;
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[prevInterval][1] <= intervals[i][0]) {
                prevInterval = i;
            } else {
                intervalsToRemove++;
                if (intervals[prevInterval][1] > intervals[i][1]) {
                    prevInterval = i;
                }
            }
        }
        return intervalsToRemove;
    }
};