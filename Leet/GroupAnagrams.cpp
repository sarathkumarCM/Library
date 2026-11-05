#include<bits/stdc++.h>
using namespace std;

class Solution {
    public:
        vector<vector<string>> groupAnagrams(vector<string>& strs) {
            vector<vector<string>> result;
            vector<unordered_map<string,vector<string>>> ans(107);

            for(auto &str: strs){
                int hash=0;
                int len=str.length();
                string hash2=str;
                sort(hash2.begin(),hash2.end());
                for(int i=0;i<len;i++){
                    hash+=(int)str[i]-'a';
                }

                ans[len][hash2].push_back(str);
            }
            for(int i=0;i<107;i++){
                if(ans[i].size()>0){
                    vector<string> temp;
                    for(auto item:ans[i]){
                        
                        temp=item.second;
                        result.push_back(temp);
                    }
                }
            }
            return result;
        }
};

int main(){
    Solution s;

    vector<string> av={"eat", "tea", "tan", "ate", "nat", "bat"};
    auto a=s.groupAnagrams(av);
    for(auto &it: a){
        for(auto &i: it){
            cout<<i<<" ";
        }
        cout<<endl;
        
    }
}

