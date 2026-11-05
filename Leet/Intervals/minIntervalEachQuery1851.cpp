#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    struct CustomCompare
    {
        bool operator()(const pair<int,int> &a, const pair<int,int> &b){
            return (a.second-a.first)>(b.second-b.first);
        }
    };
    
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<int> res;
        sort(intervals.begin(),intervals.end(),[](vector<int> &lhs,vector<int> &rhs){
            return tie(lhs[0],lhs[1])<tie(rhs[0],rhs[1]);
        });
        vector<pair<int,int>> queries2;
        for(int i=0;i<queries.size();i++){
            queries2.push_back({queries[i],i});
        }
        sort(queries2.begin(),queries2.end());
        priority_queue<pair<int,int>,vector<pair<int,int>>, CustomCompare> minH;
        int i=0;
        vector<pair<int,int>> res2;
        for(auto &it:queries2){
            while(i<intervals.size() &&intervals[i][0]<=it.first){
                minH.push({intervals[i][0],intervals[i][1]});
                i++;
            }
            if(minH.size()==0){
                res2.push_back({it.second,-1});
            }else{
                while ((!minH.empty()) && (minH.top().second<it.first))
                {
                    minH.pop();
                }
                if(minH.size()==0){
                    res2.push_back({it.second,-1});
                }else{
                    res2.push_back({it.second,minH.top().second-minH.top().first+1});
                } 
            }
        }
        sort(res2.begin(),res2.end());
        for(auto &it:res2){
            res.push_back(it.second);
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
    int m;
    cin>>m;
    vector<int> q(m);
    for(auto &it:q){
        cin>>it;
    }
    Solution s;
    auto it= s.minInterval(inp,q);
    for(auto &it2:it){
        cout<<it2<<" ";
    }

}

//best?
class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        std::vector<std::pair<int, int>> sortedIntervals;
        sortedIntervals.reserve(intervals.size());
        for (std::vector<int> const& interval : intervals) {
            sortedIntervals.emplace_back(interval[0], interval[1]);
        }
        std::sort(sortedIntervals.begin(), sortedIntervals.end());

        std::vector<std::pair<int, int>> sortedQueries;
        sortedQueries.reserve(queries.size());
        for (int const query : queries) {
            sortedQueries.emplace_back(query, sortedQueries.size());
        }
        std::sort(sortedQueries.begin(), sortedQueries.end());

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> priorityQueue;

        std::vector<int> result(sortedQueries.size());

        for (int i = 0, j = 0; i < sortedQueries.size(); i++) {
            while (j < sortedIntervals.size() && sortedQueries[i].first >= sortedIntervals[j].first) {
                priorityQueue.emplace(sortedIntervals[j].second - sortedIntervals[j].first + 1, sortedIntervals[j].second);
                j++;
            }

            while (!priorityQueue.empty() && sortedQueries[i].first > priorityQueue.top().second) {
                priorityQueue.pop();
            }

            result[sortedQueries[i].second] = priorityQueue.empty() ? -1 : priorityQueue.top().first;
        }

        return result;
    }
};

//diff approach
class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        // Understanding the problem
        // Given a 2D array intervals, where intervals[i] describes the ith interval staring at lefti and ending at righti inclusively
        // The size of any interval is defined as right[i] - left[i] + 1 (e.g. for [4, 6] 6 - 4 + 1 = 3)
        // Given an integer array queries, the answer to the jth query is the size of the smallest interval i such that left[i] <= queries[j] <= right[i]. If no such interval exists, the answer is -1
        // Return an array containing the answer to the queries

        // Brute force
        // init vector<int> res
        // init vector<int> sizes
        // for each element in intervals
            // save interval size to sizes
        // for each element in queries
            // init minSize = infi
            // for each element in intervals
                // if curr query elem is in interval
                    // minSize = min(minSize, sizes[currInt])
            // if minSize == infi
                // minSize = -1
            // res.push_back(minSize)
        
        // return res

        // sort + binary search approach
        sort(intervals.begin(), intervals.end(), [&](const vector<int> &x, const vector<int> &y) {
            return x[1] - x[0] < y[1] - y[0];
        });

        int i, n = queries.size();
        vector<int> ret(n, -1);
        set<pair<int, int>> st;
        for(i=0; i<n; i++)
            st.insert({queries[i], i});
        
        for(i=0; i<intervals.size(); i++) {
            int start = intervals[i][0], end = intervals[i][1];
            auto it = st.lower_bound({start, 0});
            while(it != st.end() && it->first <= end) {
                auto it2 = next(it);
                ret[it->second] = end - start + 1;
                st.erase(it);
                it = it2;
            }
        }
        return ret;

        
        unordered_set<int> set;
        for (int i = 0; i < queries.size(); i++) {
            queries.push_back(queries[i]);
        }
    }
};