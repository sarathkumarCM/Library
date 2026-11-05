#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int sz=height.size();
        int i=0,j=sz-1;
        while(i<sz-1 && height[i]<height[i+1]) i++; // goto the peaks
        while(j>1 && height[j]<height[j-1]) j--; //peaks
        int area=0;
        while(i<j){
            int left=i+1;
            cerr<<"i , j ("<<i<<" , "<<j<<")"<<endl;
            while(height[i]>height[left]){
                area+=height[i]-height[left];
                cerr<<"Area between "<<i<<" "<<left<<" --> "<<height[i]<<" and "<< height[left]<<" is : "<<area<<endl;
                left++;
            }
            if(height[i]<height[left]){
                i=left;
            }
            
            int right=j-1;
            while(height[j]>height[right]){
                area+=height[j]-height[right];
                cerr<<"Area between "<<right<<" "<<j<<" --> "<<height[right]<<" and "<< height[j]<<" is : "<<area<<endl;
                right--;
            }

            if(height[j]<height[right]){
                j=right;
            }
            cerr<<"Area now: "<<area<<endl;
            break;
        }
    }

    int trap(vector<int>& height,int a) {
        int sz=height.size();
        vector<int> prefixMax(sz),suffixMax(sz);
        prefixMax[0]=0;
        for(int i=1;i<sz;i++){
            prefixMax[i]=max(height[i-1],prefixMax[i-1]);
        }
        cerr<<"Prefix: ";
        for(auto i:prefixMax){
            cerr<<i<<" ";
        }
        
        suffixMax[sz-1]=0;
        for(int i=sz-2;i>=0;i--){
            suffixMax[i]=max(suffixMax[i+1],height[i+1]);
        }
        cerr<<"\nSuffixMax :";
        for(auto i:suffixMax){
            cerr<<i<<" ";
        }
        cerr<<endl;
        int area=0;
        for(int i=0;i<sz;i++){
            int re=min(suffixMax[i],prefixMax[i])-height[i];
            if(re>0)
                area+=re;
        }
        return area;
    }

    |
    |           |
    |       |   |
    |   |   |
    |   |   |
};

int main(){

    int n;
    cin>>n;
    vector<int> a(n);
    for(auto &it: a){
        cin>>it;
    }
    Solution s;
    auto ans=s.trap(a,9);
    cout<<ans<<endl;
    
}