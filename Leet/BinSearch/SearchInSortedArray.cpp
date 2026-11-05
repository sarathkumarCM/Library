#include<bits/stdc++.h>

using namespace std;

class Solution {
    public:
        int search(vector<int>& nums, int target) {
            int sz=nums.size();
            if(sz==1){
                if(nums[0]==target)
                    return 0;
                else
                    return -1;
            }
            int beg=0,end=sz-1;
            int found=-1;
            int numRot=0;
            while(beg<=end){
                if(beg==end){
                    break;
                }
                int mid=beg+(end-beg)/2;
                if(nums[mid]>nums[end]){
                    beg=mid+1;

                }else{
                    end=mid;
                }
            }
            //cerr<<" smallest is at"<<beg<<endl; 
            //numRot=(sz-beg)%sz;
            //cerr<<"NumRot: "<<numRot<<endl;
            if(beg==0 || target<=nums[sz-1]){
                //do binsearch on right side
                int beg2=beg,end2=sz-1;
                while(beg2<=end2){
                    int mid= beg2+(end2-beg2)/2;
                    if(target==nums[mid]){
                        found=mid;
                        break;
                    }
                    if(target<nums[mid]){
                        end2=mid-1;
                    }else{
                        beg2=mid+1;
                    }
                }
            }else{
                // do binsearch on left side
                int beg2=0,end2=beg-1;
                while(beg2<=end2){
                    int mid= beg2+(end2-beg2)/2;
                    if(target==nums[mid]){
                        found=mid;
                        break;
                    }
                    if(target<nums[mid]){
                        end2=mid-1;
                    }else{
                        beg2=mid+1;
                    }
                }
            }
            if(found==-1)
                return -1;
            else{
                return found; // original pos ((found+numRot)%sz)
            }
            

        }

        //best
        int search(vector<int>& nums, int target, int a) {
            int low = 0, high = nums.size() - 1;
            int pivot = -1, n = nums.size();
    
            // finding pivot
            while (low <= high) {
                int mid = low + (high - low) / 2;
                
                if (mid < n - 1 && nums[mid] > nums[mid + 1]) {
                    pivot = mid;
                    break;
                }
                else if (nums[mid] > nums[n - 1]) {
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }
    
            // If no pivot found, array is not rotated, use normal binary search
            if (pivot == -1) pivot = n - 1;
    
            // Search in both halves using binary search
            auto it1 = lower_bound(nums.begin(), nums.begin() + pivot + 1, target);
            if (it1 != nums.begin() + pivot + 1 && *it1 == target) {
                return distance(nums.begin(), it1);
            }
    
            auto it2 = lower_bound(nums.begin() + pivot + 1, nums.end(), target);
            if (it2 != nums.end() && *it2 == target) {
                return distance(nums.begin(), it2);
            }
    
            return -1; // Target not found
        }
    };

int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(auto &it:a){
        cin>>it;
    }
    int t;
    cin>>t;

    Solution s;
    cout<<s.search(a,t);
}

/*

[4,5,6,7,0,1,2]

0 1 2 4 5 6 7
1 2 4 5 6 7 0
2 4 5 6 7 0 1
4 5 6 7 0 1 2
5 6 7 0 1 2 4
6 7 0 1 2 4 5
7 0 1 2 4 5 6
0 1 2 4 5 6 7
*/