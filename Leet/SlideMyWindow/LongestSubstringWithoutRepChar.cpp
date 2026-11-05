#include<bits/stdc++.h>

using namespace std;

class Solution {
    public:
        int lengthOfLongestSubstring(string s) {
            
            unordered_set<char> seen;

            int maxlen=0;
            int maxlen2=0;
            int b=0,e=0;
            for(int i=0;i<s.size();i++){
                while(seen.find(s[i])!=seen.end()){
                    seen.erase(s[b]);
                    b++;
                }
                seen.insert(s[i]);
                //maxlen2=max(maxlen2,(int)seen.size());
                maxlen=max(maxlen,i-b+1);
            }
            cerr<<maxlen2;
            return maxlen;
        }
    };

int main(){

    string s;
    cin>>s;
    Solution ss;
    cout<<ss.lengthOfLongestSubstring(s)<<endl;
}
