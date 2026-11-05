#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int ss=s.size();
        int st=t.size();
        if(st>ss)
            return "";
        unordered_map<char, int> tc;
        unordered_map<char, int> subc;
        vector<pair<int,pair<int,int>>> res;
        for(auto &it: t){
            tc[it]++;
        }
        int l=0,r=0;
        for(;r<ss;r++){
            if(tc.find(s[l])==tc.end() && subc.size() ==0){
                l++;
            }else if(tc.find(s[r])!=tc.end()){
                subc[s[r]]++;
            }
            while(l<ss && (tc.find(s[l])==tc.end() || (subc.find(s[l])!=subc.end() &&subc[s[l]]>tc[s[l]]))){
                if(subc[s[l]]>0)
                    subc[s[l]]--;
                l++;
            }
            
            if(subc.size()>=tc.size()){
                bool psh=true;
                for(auto &it2:tc){
                    if(subc[it2.first]<it2.second){
                        psh=false;
                        break;
                    }
                }
                if(psh)
                    res.push_back(make_pair(r-l+1,make_pair(l,r)));
            }

            
        }
        while(r>l && (tc.find(s[r])==tc.end() || subc[s[r]]>tc[s[r]])){
                if(subc[s[r]]>0)
                    subc[s[r]]--;
                r--;
        }
        if(subc.size()>=tc.size()){
             bool psh=true;
            for(auto &it2:tc){
                if(subc[it2.first]<it2.second){
                    psh=false;
                    break;
                }
            }
            if(psh)
                res.push_back(make_pair(r-l+1,make_pair(l,r)));
        }
            
        if(res.size()==0)
            return "";
        else {
            sort(res.begin(),res.end(),[](pair<int ,pair<int,int>> a, pair<int ,pair<int,int>> b){return a.first<b.first;});
            return s.substr(res[0].second.first, res[0].second.second-res[0].second.first+1);
        }
    }
};

int main(){
    string s1,s2;
    cin>>s1>>s2;
    Solution s;
    cout<<s.minWindow(s1,s2);
}