#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // unordered_map<int,int> res;
        // int sz=nums.size();
        // for(int i=0;i<sz;i++){
        //     int x1=res[nums[i]-1];
        //     int x2=res[nums[i]+1];
        //     res[nums[i]]+=(x1+x2+1);
        //     res[nums[i]+1]=res[nums[i]];
        //     res[nums[i]-1]=res[nums[i]];
        // }
        // int mx=-INT_MAX;
        // for(auto &it: res){
        //     mx=max(mx,it.second);
        // }
        // return mx;
        unordered_map<int,int> res,tes;
        int sz=nums.size();
        int mx=0;
        for(int i=0;i<sz;i++){
            if(tes[nums[i]]>0)continue;
            tes[nums[i]]++;
            int x1=res[nums[i]-1];
            int x2=res[nums[i]+1];
            res[nums[i]]=(x1+x2+1); 
            res[nums[i]-x1]=res[nums[i]];
            res[nums[i]+x2]=res[nums[i]];
            mx=max(mx,res[nums[i]]);
        }
        return mx;
    }
    //best??
    int lst(vector<int>& nums){
         if (nums.empty())
            return 0;
        int result = 1;
        int* a = new int[2000000002];
        int s = nums.size();
        for (int i = 0; i < s; i++) {
            nums[i] += 1000000000;
            if (a[nums[i]]) {
                swap(nums[i], nums[s - 1]);
                s--;
                i--;
                continue;
            }
            a[nums[i]] = 1;
        }

        for (int i = 0; i < s; i++) {
            int x = nums[i] + 1;
            while (a[x] == 1) {
                a[x] = -1;
                a[nums[i]]++;
                result = max(result, a[nums[i]]);
                x++;
            }
            if (a[x] > 1) {
                a[nums[i]] += a[x];
                result = max(result, a[nums[i]]);
            }
        }
        delete[] a;
        return result;
    }
};

int main(){
    int nums;
    cin>>nums;
    vector<int> inp(nums);
    for(auto &it: inp){
        cin>>it;
    }
    Solution s;
    int len=s.longestConsecutive(inp);
    cout<<len<<endl;

}
/*

    0 - 1 (-1=0, 1=0) -> 0-0=0-1, 0+



    0-1 (-1 1)  0,2,3,4,5,6,7,8
    3-1 (2 4)
    7-1 (6 8)
    2-2 (1=0, 3=1)-> 3=2??
    5=1 (4=0, 6=0)
    8=2  (7=1, 9=0), 7=2,
    4=4  (3=2, 5=1), 5=4 or 4=3 (3=1,5=1)
    6=6   (5=4, 7=1), 7=6,  
    1=

    2= 1 (1=0,3=0), 1=1,3=1
    3=  2, (2=2, 4=2)
    1=3 (2=3, 0=0)
    4=3 3,5= 3


*/