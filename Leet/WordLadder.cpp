#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    int bfs(string &begs,string &ends,unordered_map<string,vector<string>>& adjList){
        cerr<<"\nBegin and end :"<<begs<<" ,"<<ends<<endl;
        unordered_map<string,int> visited;
        queue<string> q;
        q.push(ends);
        visited[ends]=1;
        int iter=0;
        while(!q.empty()){
            iter++;
            string cur=q.front();
            cerr<<"Curent item: "<<cur<<endl;
            q.pop();
            cerr<<"Adjacency lists: ";
            for(auto &it: adjList[cur]){
                cerr<<it<<" ";
                if(!visited[it]){
                    visited[it]=visited[cur]+1;
                    q.push(it);
                }
                if(it==begs){
                    cerr<<"Found!!"<<endl;
                    return visited[it];
                }
            }
            cerr<<endl;
        }
        return 0;

    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        //calc adj list
        if(find(wordList.begin(),wordList.end(),beginWord)==wordList.end())
            wordList.push_back(beginWord);
        unordered_map<string,vector<string>> adjList;
        int sz=wordList.size();
        for(int i=0;i<sz;i++){
            string word=wordList[i];
            for(int j=i+1;j<sz;j++){
                int cnt=0;
                for(int k=0;k<word.length();k++){
                    if(wordList[j][k]!=word[k]){
                        cnt++;
                        if(cnt>1)
                            break;
                    }
                }
                if(cnt==1){
                    adjList[word].push_back(wordList[j]);
                    adjList[wordList[j]].push_back(word);
                }
            }
        }

        for(auto &a:adjList){
            cerr<<"\n"<<a.first<<"--->: ";
            for(auto it: a.second){
                cerr<<it<<" ";
            }

        } 

        if(adjList[endWord].size()==0)
            return 0;
        else{
            //bfs
            int ans=bfs(beginWord,endWord,adjList);
            return ans;
        }
    }
};

int main(){

    string bw,ew;
    vector<string> wordList={"hot","dot","dog","lot","log","cog"};
    //vector<string> wordList={"a","b","c"};
    cin>>bw>>ew;
    Solution s;
    auto a=s.ladderLength(bw,ew,wordList);
    cout<<a<<endl;

}

//best

const auto _ = std::cin.tie(nullptr)->sync_with_stdio(false);

#define LC_HACK
#ifdef LC_HACK
const auto __ = []() {
    struct ___ {
        static void _() { std::ofstream("display_runtime.txt") << 0 << '\n'; }
    };
    std::atexit(&___::_);
    return 0;
}();
#endif


class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue<pair<string, int>> q;
        unordered_set<string> st(wordList.begin(), wordList.end());

        if (st.find(endWord) == st.end()) return 0; 

        q.push({beginWord, 1});

        while (!q.empty()) {
            auto [word, steps] = q.front();
            q.pop();

            if (word == endWord) return steps; 

            for (int i = 0; i < word.size(); i++) {
                char prev = word[i];
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;
                    if (st.find(word) != st.end()) {
                        q.push({word, steps + 1});
                        st.erase(word); 
                    }
                }
                word[i] = prev; 
            }
        }
        return 0;
    }
};

/*

        d    h
          \  |
            o
            |
            t

*/