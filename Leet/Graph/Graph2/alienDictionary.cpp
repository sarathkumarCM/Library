#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
      bool dfs(char src, unordered_map<char,unordered_set<char>> &adj, unordered_set<char> &vis, string &topSort,unordered_set<char> &path){
        if(path.find(src)!=path.end()) return false;
        if(vis.find(src)!=vis.end()) return true;
        vis.insert(src);
        path.insert(src);
        bool res=true;
        for(auto &it:adj[src]){
            res =res && dfs(it,adj,vis,topSort,path);
        }
        topSort.push_back(src);
        path.erase(src);
        return res;
    }
    string foreignDictionary(vector<string>& words) {
        unordered_map<char,unordered_set<char>> adj;
        int n=words.size();
        for(int i=0;i<n;i++){
            for(int j=0;j<words[i].size();j++){
                adj[words[i][j]]={};
            }
        }
        for(int i=0;i<n-1;i++){
            string st=words[i];
            string st2=words[i+1];
            bool dn=true;
            for(int k=0;(k<st.size() && k<st2.size());k++){
                if(st[k]!=st2[k]){
                    adj[st[k]].insert(st2[k]);
                    dn=false;
                    break;
                }
            }
            if(dn && st2.size()<st.size()) // stupidity
                return "";
        }

        // for(auto &it:adj){
        //     cerr<<"\nNode: "<<it.first<<": has ";
        //     for(auto &it2:it.second){
        //         cerr<<it2<<" ";
        //     }
        // }

        //topo sort on this
        string topSort;
        unordered_set<char> vis,path;

        for(auto &it:adj){
            if(vis.find(it.first)==vis.end()){
                if(!dfs(it.first,adj,vis,topSort,path))
                    return "";
            }
        }

        reverse(topSort.begin(),topSort.end());
        return topSort;
    }
};

int main(){
    int n;
    cin>>n;
    vector<string> inp(n);
    for(auto &it:inp){
        cin>>it;
    }
    Solution s;
    cout<<s.foreignDictionary(inp);
}

//Best

class Solution3 {
public:
    unordered_map<char, unordered_set<char>> adj;
    unordered_map<char, bool> visited;
    string result;

    string foreignDictionary(vector<string>& words) {
        for (const auto& word : words) {
            for (char ch : word) {
                adj[ch];
            }
        }

        for (size_t i = 0; i < words.size() - 1; ++i) {
            const string& w1 = words[i], & w2 = words[i + 1];
            size_t minLen = min(w1.length(), w2.length());
            if (w1.length() > w2.length() &&
                w1.substr(0, minLen) == w2.substr(0, minLen)) {
                return "";
            }
            for (size_t j = 0; j < minLen; ++j) {
                if (w1[j] != w2[j]) {
                    adj[w1[j]].insert(w2[j]);
                    break;
                }
            }
        }

        for (const auto& pair : adj) {
            if (dfs(pair.first)) {
                return "";
            }
        }

        reverse(result.begin(), result.end());
        return result;
    }

    bool dfs(char ch) {
        if (visited.find(ch) != visited.end()) {
            return visited[ch];
        }

        visited[ch] = true;
        for (char next : adj[ch]) {
            if (dfs(next)) {
                return true;
            }
        }
        visited[ch] = false;
        result.push_back(ch);
        return false;
    }
};

//worse than mine
class Solution2 {
public:
    string foreignDictionary(vector<string>& words) {
        unordered_map<char,unordered_set<char>> adj;
        unordered_map<char,int> inDegree;

        int n = words.size();

        for(string s:words){
          for(char ch:s){
            adj[ch]=unordered_set<char>();
            inDegree[ch]=0;
          }
        }

        for(int i=0;i<n-1;i++){
          string word1 = words[i];
          string word2 = words[i+1];

          int minLen = min(word1.length(),word2.length());

          if(word1.length()>word2.length() && word1.substr(0,minLen)==word2.substr(0,minLen)){
            return "";
          }

          for(int j=0;j<minLen;j++){
            if(word1[j]!=word2[j]){
              if(!adj[word1[j]].count(word2[j])){
                adj[word1[j]].insert(word2[j]);
                inDegree[word2[j]]++;
              }
              break;
            }
          }


        }

        queue<char> q;

        for(auto &[c,deg]:inDegree){
          if(deg==0){
            q.push(c);
          }
        }

        string res = "";

        while(!q.empty()){
          char ch = q.front();
          q.pop();

          res+=ch;

          for(auto &it:adj[ch]){
            inDegree[it]--;
            if(inDegree[it]==0){
              q.push(it);
            }
          }
        }

        return res.size()==inDegree.size() ? res : "";

    }
};
