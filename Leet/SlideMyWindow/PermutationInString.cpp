#include<bits/stdc++.h>

using namespace std;

class Solution {
    public:
        bool checkInclusion(string s1, string s2) {
            if(s1.size()>s2.size())
                return false;
            //unordered_map<char,int> s1m;
            int s1m[26]={0};
            unordered_set<char> seen;
            for(auto &it:s1){
                s1m[(int)it-'a']++;
            }
            
            int sz2=s2.size();
            int sz1= s1.size();
            int b=0,e=0;
            auto s1mc=s1m;
            int i=0;
            for(;i<sz2;i++){
                int s2m[26]={0};
                for(int j=0;j<sz1 && (i+j)<sz2;j++){
                    if(s1m[(int)s2[i+j]-'a']==0){
                        break;
                    }
                    s2m[(int) s2[i+j]-'a']++;
                }
                int fnd=true;
                for(int k=0;k<26;k++){
                    if(s1m[k]!=s2m[k]){
                        fnd=false;
                        break;
                    }
                }
                if(fnd)
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