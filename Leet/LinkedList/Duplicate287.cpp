class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        bitset<100001> b;
        for(auto &it:nums){
            if(b[it])
                return it;
            b.set(it);
        }
        return -1;
    }
};

//best

class Solution {
public:
    int findDuplicate(vector<int>& arr) {
     int index=-1;
     int ans=0;
     for(int i=0;i<arr.size();i++)
     {
        index=abs(arr[i]);
        if(arr[index]<0)
        {
            ans=index;
            break;
        }
        arr[index] *= -1;
     }
     return ans;
    }
};

//no mod

int findDuplicate3(vector<int>& nums)
{
	if (nums.size() > 1)
	{
		int slow = nums[0];
		int fast = nums[nums[0]];
		while (slow != fast)
		{
			slow = nums[slow];
			fast = nums[nums[fast]];
		}

		fast = 0;
		while (fast != slow)
		{
			fast = nums[fast];
			slow = nums[slow];
		}
		return slow;
	}
	return -1;
}