#include<bits/stdc++.h>

using namespace std;

class Solution {
    public:
        int characterReplacement(string s, int k) {
            unordered_map<char,int> freq;
            int maxlen=0;
            int b=0;
            int maxFreq=0;
            for(auto i=0;i<s.size();i++){
                freq[s[i]]++;
                maxFreq=max(maxFreq,freq[s[i]]);
                while(i-b+1 - maxFreq >k){
                    freq[s[b]]--;
                    b++;
                }
                maxlen=max(maxlen,i-b+1);
            }
            return maxlen;
        }

        // Best

        int characterReplacement(string s, int k,int j) {
            int l=0, r=0, maxlen=0, maxf=0;
            int hash[26]= {0};
            while(r<s.size()){
                hash[s[r]-'A']++;
                maxf=max(maxf,hash[s[r]-'A']);
                if((r-l+1)-maxf>k){
                    hash[s[l]-'A']--;
                    maxf=0;
                    l=l+1;
                }
                if((r-l+1)-maxf<=k)
                maxlen=max(maxlen,r-l+1);
                r++;
            }
            return maxlen;
        }
    };

int main(){
    string s;
    int k;
    cin>>s;
    cin>>k;
    Solution ss;
    cout<<ss.characterReplacement(s,k);

}