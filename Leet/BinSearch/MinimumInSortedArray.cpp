#include <bits/stdc++.h>

using namespace std;
class Solution {
    public:
        int findMin(vector<int>& nums) {
            int sz=nums.size();
            int left=0, right=sz-1;
            while(left<=right){
                if(left==right)
                {
                    //cerr<<"Left "<<left<<endl;
                    return nums[left];
                }
                int mid=left+(right-left)/2;
                if(nums[mid]> nums[right]){
                    left=mid+1;
                }else{
                    right=mid;
                }
            }
            //cerr<<"Left 2: "<<left<<endl;
            return nums[left];
        }
    };

int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(auto &it:a){
        cin>>it;
    }

    Solution s;
    cout<<s.findMin(a);

}


/*
1 2 3 4 5 -- mid= 3  mid<
2 3 4 5 1
3 4 5 1 2
4 5 1 2 3
5 1 2 3 4
1 2 3 4 5

1 2 3 4 -- mid= 1+ (4-1)/2 = 2 = 3 > high== good
2 3 4 1 -- mid= 4 , 4>1 y check right 1 1
3 4 1 2 -- mid =1 1>2 X check left
4 1 2 3 -- mid =2 2 >3 X check left --
*/