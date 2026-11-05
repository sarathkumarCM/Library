#include<bits/stdc++.h>

using namespace std;

class Solution {
public:

    void backTrack(int op,int cls,int n, vector<string>& results, string &s ){

        if(op==cls && op==n){
            results.push_back(s);
            return;
        }else{
            if(op<n){
                s+='(';
                backTrack(op+1,cls,n,results,s);
                s.pop_back();
            }
            if(cls<op){
                s+=')';
                backTrack(op,cls+1,n,results,s);
                s.pop_back();
            }
        }

    }
    vector<string> generateParenthesis(int n) {
        string s;
        vector<string> results;
        backTrack(0,0,n,results,s);
        return results;
    }
};

//BEst

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<vector<string>> res(n + 1);
        res[0] = {""};

        for (int k = 0; k <= n; ++k) {
            for (int i = 0; i < k; ++i) {
                for (const string& left : res[i]) {
                    for (const string& right : res[k - i - 1]) {
                        res[k].push_back("(" + left + ")" + right);
                    }
                }
            }
        }

        return res[n];
    }
};


int main(){
    int n;
    cin>>n;
    Solution s;
    auto res=s.generateParenthesis(n);
    for(auto &it: res){
        cout<<it<<" ";
    }
    cout<<endl;
    return 0;
}