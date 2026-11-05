#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool dfs(string s,vector<string> &wordDict, int i, string curWord){
        if(i>=wordDict.size()||i<0){
            return false;
        }
        if(s==curWord){
            return true;
        }
        string newCur=curWord+wordDict[i];
        if(newCur.size()>s.size()){
            return false;
        }
        cerr<<"new Cur: "<<newCur<<", i :"<<i<<", wordDict: "<<wordDict[i]<<endl;
        if(newCur==s){
            return true;
        }
        bool ans=false;
        if(s.find(newCur)!=string::npos){
            //explore
            ans=ans|| dfs(s,wordDict,i,newCur)||dfs(s,wordDict,i+1,newCur);
        }
        return ans||dfs(s,wordDict,i+1,curWord);
    }
     bool dfs2(string s,vector<string> &wordDict, int i, string curWord){
        cerr<<i<<endl;
        if(i>=wordDict.size()||i<0){
            cerr<<"here for i"<<i<<endl;
            return false;
        }
        if(s==curWord){
            return true;
        }
        string newCur=curWord+wordDict[i];
        cerr<<"new Cur: "<<newCur<<", i :"<<i<<", wordDict: "<<wordDict[i]<<endl;
        if(newCur==s){
            return true;
        }
        bool ans=false;
        if((s.find(newCur)!=string::npos) && (newCur.size()<s.size())){
            ans=ans || dfs2(s,wordDict,i,newCur) || dfs2(s,wordDict,i+1,newCur);
        }
        ans = ans|| dfs2(s,wordDict,i+1,curWord);
        return ans;
    }

    bool dfs3(string s, unordered_set<string> &dp, int start){
        if(start==s.size()) return true;
        for(int end=start+1;end<=s.size();end++){
            string word=s.substr(start,end-start);
            if(dp.count(word)&& dfs3(s,dp,end)){
                return true;
            }
        }
        return false;

    }
    bool dfs3Memo(string s, unordered_set<string> &dp, int start, vector<int> &mem){
        if(start==s.size()) return true;
        if(mem[start]!=-1) return (mem[start]==0?false:true);
        for(int end=start+1;end<=s.size();end++){
            string word=s.substr(start,end-start);
            mem[start]=(dp.count(word)&& dfs3Memo(s,dp,end,mem))==true?1:0;
            if(mem[start]){
                return true;
            }
        }
        return false;

    }
    bool wordBreak(string s, vector<string>& wordDict) {
        return dfs2(s,wordDict,0,"");
    }
    bool wordBreakMemo(string s, vector<string>& wordDict) {
        unordered_set<string> dp(wordDict.begin(), wordDict.end());
        vector<int> memo(s.size()+1,-1);
        return dfs3Memo(s,dp,0,memo);


    }

    bool wordBreakDP(string s, vector<string>& wordDict) {
        int n=s.size();
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size()+1,false);
        for(int i=0;i<n;i++){
            int j=i>20?i-20:0;
            while(j<=i){
                string s1=s.substr(j,i-j+1);
                if(j==0 || (j>0 && dp[j-1])){
                    if(dict.count(s1)) dp[i]=true;
                }
                j++;
            }
        }
        return dp[n-1];
    }
};

int main(){
    int n;
    cin>>n;
    string q;
    cin>>q;
    vector<string> inp(n);
    for(auto &it: inp){
        cin>>it;
    }
    Solution ss;
    cout<<ss.wordBreakDP(q,inp); //working

}

//best
class Solution2{

    bool solve(string& s, vector<string>& wordDict,
               unordered_map<string, int>& mp, int ind,vector<int>& dp) {

        int n = s.size();

       if (ind == s.size()) return true;

       if(dp[ind]!=-1)
       {
        return dp[ind];
       }

        string s1 = "";

        for (int i = ind; i < s.size(); i++) {
            s1 += s[i];

            if (mp.find(s1) != mp.end()) {

                if(solve(s, wordDict, mp, i + 1,dp)){
                    return dp[ind] =  true;
                };
            }
        }

        return dp[ind] =  false;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {

        unordered_map<string, int> mp;

        int n = s.size();

        vector<int>dp(n,-1);

        for (int i = 0; i < wordDict.size(); i++) {
            mp[wordDict[i]]++;
        }

        return solve(s, wordDict, mp, 0,dp);
    }
};