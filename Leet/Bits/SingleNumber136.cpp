class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int nm=nums[0];
        for(int i=1;i<nums.size();i++)
            nm=nm^nums[i];

        return nm;
    }
};