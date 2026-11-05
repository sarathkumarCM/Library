#include<bits/stdc++.h>

using namespace std;
class Solution {
    public:
        int search(vector<int>& nums, int target) {
            sort(nums.begin(),nums.end());
            int idx=lower_bound(nums.begin(),nums.end(),target)-nums.begin();
            
            if(idx<nums.size()){
                if(nums[idx]!=target)
                    return -1;
                return idx;
            }
            else
                return -1;
    
        }
    };

// best way to do binSearch
