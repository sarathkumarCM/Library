#include<bits/stdc++.h>

using namespace std;
class Solution {
public:
    bool isPalindrome(string s) {
        int sz=s.size();
        int j=sz-1;
        int i=0;
        for(;i<sz/2;i++,j--){
            if(s[i]!=s[j]) return false;
        }
        return true;
    }
};

int main(){
    string st;
    cin>>st;
    Solution s;
    cout<<s.isPalindrome(st)<<endl;

}
