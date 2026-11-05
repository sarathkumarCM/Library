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
    bool canAttendMeetings(vector<Interval>& intervals) {
        if(intervals.size()<=1){
            return true;
        }
        sort(intervals.begin(),intervals.end(),[](const Interval &a, const Interval &b){
            return tie(a.start,a.end)<tie(b.start,b.end);
        });
        // for(auto &it:intervals){
        //     cerr<<it.start<<" "<<it.end<<endl;
        // }
        Interval prev=intervals[0];
        for(int i=1;i<intervals.size();i++){
            if(intervals[i].start<prev.end){
                return false;
            }
            prev=intervals[i];
        }
        return true;
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
    cout<<s.canAttendMeetings(inp);
}

//best -- how tf :D
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
    bool canAttendMeetings(vector<Interval>& intervals) {
        if(intervals.size()==0) return true;
        for(int i=0;i<intervals.size()-1;i++){
            for (int j=i+1;j<intervals.size();j++){
                if(intervals[j].start>intervals[i].start &&
                   intervals[j].start<intervals[i].end){
                    return false;
                   }
                if(intervals[j].end<intervals[i].end &&
                   intervals[j].end>intervals[i].start){
                    return false;
                   }
                if(intervals[j].start==intervals[i].start &&
                   intervals[j].end==intervals[i].end){
                    return false;
                   }
                if(intervals[j].start==intervals[i].start &&
                   intervals[j].end>intervals[i].end){
                    return false;
                   }
            }
        }
        return true;
    }
};
