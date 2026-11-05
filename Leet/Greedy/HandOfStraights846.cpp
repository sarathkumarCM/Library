#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n=hand.size();
        if(n%groupSize!=0){
            return false;
        }
        unordered_map<int,int> mp;
        for(int i=0;i<n;i++){
            mp[hand[i]]++;
        }
        sort(hand.begin(),hand.end());
        for(int i=0;i<n;i++){
            bool nd=false;
            if(mp[hand[i]]<=0)
                continue;
            for(int j=0;j<groupSize;j++){
                 auto it1=mp.find(hand[i]+j);
                 if(it1==mp.end()|| it1->second<=0){
                    nd=true;
                    break;
                 }
            }
            if(nd){
                continue;
            }
            for(int j=0;j<groupSize;j++){
                mp[hand[i]+j]--;
            }

        }

        for(auto &it:mp){
            if(it.second!=0)
                return false;
        }
        return true;
    }
};

int main(){
    int n,g;
    cin>>n;
    vector<int> inp(n);
    for(auto &it:inp){
        cin>>it;
    }
    cin>>g;
    Solution s;
    cout<<s.isNStraightHand(inp,g);
}

//best
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        // If not divisible, can't form groups
        if (hand.size() % groupSize != 0) return false;

        // Sort the hand
        sort(hand.begin(), hand.end());
        vector<bool> used(hand.size(), false);

        // Try to form groups
        for (int i = 0; i < hand.size(); i++) {
            if (used[i]) continue;
            used[i] = true;
            int count = 1, next = hand[i] + 1;

            // Search for next consecutive numbers
            for (int j = i + 1; j < hand.size() && count < groupSize; j++) {
                if (!used[j] && hand[j] == next) {
                    used[j] = true;
                    next++;
                    count++;
                }
            }
            if (count != groupSize) return false;
        }
        return true;
    }
};

//best as per site
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if (hand.size() % groupSize != 0) return false;

        unordered_map<int, int> count;
        for (int num : hand) count[num]++;

        sort(hand.begin(), hand.end());
        for (int num : hand) {
            if (count[num] > 0) {
                for (int i = num; i < num + groupSize; i++) {
                    if (count[i] == 0) return false;
                    count[i]--;
                }
            }
        }
        return true;
    }
};

//best
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        // If not divisible, can't form groups
        if (hand.size() % groupSize != 0) return false;

        // Sort the hand
        sort(hand.begin(), hand.end());
        vector<bool> used(hand.size(), false);

        // Try to form groups
        for (int i = 0; i < hand.size(); i++) {
            if (used[i]) continue;
            used[i] = true;
            int count = 1, next = hand[i] + 1;

            // Search for next consecutive numbers
            for (int j = i + 1; j < hand.size() && count < groupSize; j++) {
                if (!used[j] && hand[j] == next) {
                    used[j] = true;
                    next++;
                    count++;
                }
            }
            if (count != groupSize) return false;
        }
        return true;
    }
};