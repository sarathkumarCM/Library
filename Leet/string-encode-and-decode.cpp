#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    string encode(vector<string>& strs) {
        string result="";
        for(auto &str: strs){
            int len=str.length();
            result+=to_string(len)+"%"+str;
        }
        return result;
    }

    vector<string> decode(string s) {
        vector<string> ret;
        int lengt=s.length();
        int i=0;
        while(i<lengt){
            int j=i;
            while(s[j]!='%'){
                j++;
            }
            int len=stoi(s.substr(i,j-i));
            i=j+1;
            j=i+len;
            string st=s.substr(i,len);
            ret.push_back(st);
            i=j;
        }
        return ret;
    }
};


int main(){

    Solution s;
    int n;
    cin>>n;
    vector<string> inp(n);
    for(auto &it: inp){
        cin>>it;
    }
    auto ans=s.encode(inp);
    cerr<<" ans: "<<ans<<endl;
    auto re=s.decode(ans);
    for(auto &r:re){
        cout<<r<<endl;
    }
    return 0;
}
