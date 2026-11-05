#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n=digits.size();
        int c=1;
        int prev=1;
        for(int i=n-1;i>=0;i--){
            int sm=digits[i]+c;
            if(sm>9){
                c=1;
            }else{
                c=0;
            }
            digits[i]=sm%10;
        }
        if(c!=0)
            digits.insert(digits.begin(),1);

        return digits;
    }
};

int main(){
    int n;
    cin>>n;
    vector<int> inp(n);
    for(auto &it:inp)cin>>it;
    Solution ss;
    auto res=ss.plusOne(inp);
    for(auto &it:res){
        cout<<it;
    }
}

//best
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        for(int i = digits.size()-1; i>=0; i--){
            if(digits[i] < 9){
                digits[i]++;
                return digits;
            }
            digits[i] = 0;
        }
        digits.insert(digits.begin(), 1);
        return digits;
    }
};
//exits early