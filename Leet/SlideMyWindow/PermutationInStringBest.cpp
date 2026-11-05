#include<bits/stdc++.h>

using namespace std;

class Solution {
    public:
        bool checkInclusion(string s1, string s2) {
            if(s1.size()>s2.size())
                return false;
            //unordered_map<char,int> s1m;
            vector<int> s1m(26,0);
            vector<int> s2m(26,0);
            for(auto &it:s1){
                s1m[(int)it-'a']++;
            }
            
            int sz2=s2.size();
            int sz1= s1.size();
            int b=0,e=0;
            auto s1mc=s1m;
            int l=0,r=0;
            for(;r<sz2;r++){
                s2m[s2[r]-'a']++;

                if(r-l+1>sz1){
                    s2m[s2[l]-'a']--;
                    l++;
                }
                if(s1m==s2m)
                    return true;
            }
            
            return false;

        }
    };

int main(){
    string s1,s2;
    cin>>s1>>s2;
    Solution s;
    cout<<s.checkInclusion(s1,s2);
}