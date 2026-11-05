#include<bits/stdc++.h>

using namespace std;

class Interval {
    public:
        int start, end;
        Interval(int start, int end) {
            this->start = start;
            this->end = end;
        }
        Interval(){

        }

};
 
class Solution {
public:
    
    int minMeetingRooms(vector<Interval>& intervals) {
        if(intervals.size()==0) return 0;
        if(intervals.size()==1) return 1;
        sort(intervals.begin(),intervals.end(),[](const Interval &a, const Interval &b){
            return a.start<b.start;
        });
        priority_queue<int,vector<int>,greater<int>> minH;
        minH.push(intervals[0].end);
        for(int i=1;i<intervals.size();i++){
            if(minH.top()<=intervals[i].start){
                minH.pop();
            }
            minH.push(intervals[i].end);
        }
        return minH.size();
        
    }
};

int main(){
    int i;
    cin>>i;
    vector<Interval> inp(i);
    for(auto &it:inp){
        cin>>it.start>>it.end;
    }
    Solution s;
    cout<<s.minMeetingRooms(inp);
}


//best no sort
/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        using TimeToStart = std::pair<int, int>;
        //auto cmp = [](TimeToStart const& lhs, TimeToStart const& rhs) {
        //    if (lhs.first != rhs.first) {
        //        return lhs.first > rhs.first;
        //    }
        //    return lhs.second;
        //};
        std::priority_queue<TimeToStart, std::vector<TimeToStart>, std::greater<TimeToStart>> pq;

        for (auto& i : intervals) {
            pq.push({i.start, 1});
            pq.push({i.end, 0});
        }

        int currentCount = 0;
        int maxCount = 0;
        while (!pq.empty()) {
            if (pq.top().second == 1) {
                maxCount = std::max(maxCount, ++currentCount);
            }
            else {
                --currentCount;
            }
            pq.pop();
        }
        return maxCount;
    }
};

//easier 
/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        /*
        [(0,40),(5,10),(15,20)]
        meeting_rooms = 1
        max_meeting_rooms = 2
        s -> [0, 5, 15]
                       i
        e -> [10, 20, 40]
                  j
        */
        int n = intervals.size();
        vector<int> start_times;
        vector<int> end_times;
        for(Interval interval: intervals){
            start_times.push_back(interval.start);
            end_times.push_back(interval.end);
        }
        sort(start_times.begin(), start_times.end());
        sort(end_times.begin(), end_times.end());

        int meeting_rooms = 0;
        int max_meeting_rooms = 0;
        int i = 0, j = 0;
        while(i<n && j<n){
            if(start_times[i] < end_times[j]){
                meeting_rooms++;
                max_meeting_rooms = max(max_meeting_rooms, meeting_rooms);
                i++;
            } else{
                meeting_rooms--;
                j++;
            }
        }
        return max_meeting_rooms;
    }
};



