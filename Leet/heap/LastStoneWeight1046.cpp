#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        //fill prioq
        priority_queue<int> q;
        for(auto &it:stones){
            q.push(it);
        }
        while(q.size()>1){
            int t1=q.top();
            q.pop();
            int t2=q.top();
            q.pop();
            if(abs(t1-t2)>0){
                int t=abs(t1-t2);
                q.push(t);
            }else if(abs(t1-t2)==0&& q.size()==0){
                q.push(0);
            }
        }
        return q.top();
    }
};

int main(){
    int n;
    cin>>n;
    vector<int> nums(n);
    for(auto &it: nums){
        cin>>it;
    }
    Solution s;
    cout<<s.lastStoneWeight(nums);
}