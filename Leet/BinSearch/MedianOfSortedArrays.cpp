#include<bits/stdc++.h>

using namespace std;

class Solution {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
            int sz1=nums1.size(),sz2=nums2.size();
            vector<int> &a=nums1;
            vector<int> &b=nums2;
            int tot=sz1+sz2;
            int half=(tot+1)/2;

            if(sz1>sz2){
                swap(a,b);
            }

            // assuming a is always the smallest
            int l=0;
            int r=a.size();
            while(l<=r){

                int i=(l+r)/2; // mid of A
                int j=half-i; // rest for the median
                int Aleft=(i>0)?a[i-1]:INT_MIN;
                int Bleft=(j>0)?a[j-1]:INT_MIN;
                int Aright=(i<a.size())?a[i]:INT_MAX;
                int Bright=(i<b.size())?b[j]:INT_MAX;

                /*
                ideal 
                aleft <= bright 
                bleft<=Aright
                means
                aleft  bleft bright aright or
                aleft bleft aright bright
                bleft aleft bright aright
                bleft aleft aright bright
                
                */

                if(Aleft<=Bright && Bleft<=Aright){
                    if(tot%2!=0)
                        return max(Aleft,Bleft);
                    return (max(Aleft,Bleft)+min(Bright,Aright))/2.0;
                }else if(Aleft>Bright){
                    /*
                    bleft bright aleft aright shift right to the left side
                    */
                    r=i-1;
                }else{
                    // on left side
                    l=i+1;
                }
            }

            return -1;  


        }
    };

int main(){
    int n,m;
    cin>>n>>m;
    vector<int> a(n),b(m);
    for(auto &it: a){
        cin>>it;
    }
    for(auto &it: b){
        cin>>it;
    }
    Solution s;
    auto ans=s.findMedianSortedArrays(a,b);
    cout<<ans<<endl;

}

/*

1 4 7
2 5
 sirted == 1 2 4 5 7 == median =4

1 4 7 -- 
2 5 8
aleft=

-- sorted = 1 2 4 5 7 8 = median= 4+5/2 =4.5

5 55 60

10 25 30

10 25 30 40 55 60 --3 4


 40 55 60  10 25 30
*/