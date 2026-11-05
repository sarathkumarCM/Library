#include<bits/stdc++.h>

using namespace std;

struct UnionFind{
    int n;
    vector<int> p,r;
    UnionFind(int sz):n{sz}{
        r.resize(sz,0);
        p.resize(sz,-1);
        for(int i=0;i<sz;i++){
            p[i]=i;
        }
    }
    int find(int i){
        if(p[i]==i){
            return i;
        }
        p[i]=find(p[i]);
        return p[i];
    }
    int find2(int i){
        int pi=p[i];
        while(pi!=p[pi]){
            p[pi]=p[p[pi]];
            pi=p[pi];
        }
        return pi;
    }
    bool un(int i,int j){
        int a=find(i);
        int b=find(j);
        if(a==b) return false;
        if(r[a]>r[b]){
            p[b]=a;
        }else if(r[b]>r[a]){
            p[a]=b;
        }else{
            p[a]=b;
            r[b]++;
        }
        return true;
    }

};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> ans;
        unordered_set<int> s;
        for(auto &it:edges){
            s.insert(it[0]);
            s.insert(it[1]);
        }
        UnionFind uf(s.size()+1);
        for(auto &it:edges){
            if(!uf.un(it[0],it[1])){
                ans.push_back(it[0]);
                ans.push_back(it[1]);
            }
        }
        return ans;
    }
};

int main(){

     int k;
     cin>>k;
     vector<vector<int>> inp(k,vector<int>(2));
     for(auto &it:inp){
        cin>>it[0]>>it[1];
     }
     cerr<<"here?"<<endl;
     Solution s;
     vector<int> sol;
     sol=s.findRedundantConnection(inp);
     for(auto &it:sol){
        cout<<it<<" ";
     }
}