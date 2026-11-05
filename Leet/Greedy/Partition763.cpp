#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int sz=s.size();
        vector<int> res;
        unordered_map<int,int> mp;
        for(int i=0;i<sz;i++){
            mp[s[i]-'a']=i;
        }
        for(int i=0;i<sz;i++){
            int left=i;
            int right=mp[s[i]-'a'];
            while(left<right && right<sz){
                //cerr<<"Left:"<<left<<" item: "<<s[left]<<" right:"<<right<<endl;
                left++;
                if(mp[s[left]-'a']>right){
                    right=mp[s[left]-'a'];
                }
            }
            
            res.push_back(right-i+1);
            i=right;
        }
        return res;
    }
};

int main(){
    string s;
    cin>>s;
    Solution ss;
    auto res=ss.partitionLabels(s);
    for(auto &it:res){
        cout<<it<<" ";
    }
}

//best?
class Solution2 {
public:
    vector<int> partitionLabels(string s) {
        unordered_map<char,int>mp;
        vector<int>res;
        for(int i=0;i<s.length();i++)
        {
            mp[s[i]]=i;
        }

        int first=0,lastOccurance=0;

        for(int i=0;i<s.length();i++)
        {
            lastOccurance=max(lastOccurance,mp[s[i]]);

            if(lastOccurance==i)
            {
                res.push_back(lastOccurance-first+1);
                first=lastOccurance+1;
            }
        }
        return res;
    }
};