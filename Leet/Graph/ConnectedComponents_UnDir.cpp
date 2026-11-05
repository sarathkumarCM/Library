#include<bits/stdc++.h>
using namespace std;

struct UnionFind{
    vector<int> p;
    vector<int> r;
    int n;
    UnionFind(int sz):n{sz}{
        r.resize(sz,0);
        p.resize(sz,-1);
        for(int i=0;i<sz;i++){
            p[i]=i;
        }
    }

    int find(int x){
        return (p[x]==x)?x:p[x]=find(p[x]);
    }
    bool unionFind(int i,int j){
        int a=find(i),b=find(j);
        if(a==b){
            return false; // cant union since same
        }else{
            if(r[a]>r[b]){
                p[b]=a;
            }else if(r[b]>r[a]){
                p[a]=b;
            }else{
                p[a]=b;
                r[b]++;
            }
        }
        return true;
    }
    int returnCon(){
        for(int i=0;i<n;i++){
            int x=find(i);
        }
        unordered_set<int> s(p.begin(),p.end());
        return s.size();
    }
};

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        UnionFind uf(n);
        for(auto &it:edges){
            uf.unionFind(it[0],it[1]);
        }
        return uf.returnCon();
    }
};

int main(){

    int n;
    cin>>n;
    int k;
    cin>>k;
    vector<vector<int>> inp(k,vector<int>(2,0));
    for(auto &it:inp){
        cin>>it[0]>>it[1];
    }
    Solution s;
    cout<<s.countComponents(n,inp);

}

//Best?

class Solution {
public:
    vector<int> parent, size;

    int FindParent(int x) {
        if(parent[x] == x) return x;
        return parent[x] = FindParent(parent[x]);
    }

    void merge(int x, int y) {
        int xp = FindParent(x);
        int yp = FindParent(y);

        if(xp == yp) return;

        if(size[xp] < size[yp]) {
            parent[xp] = yp;
            size[yp] += size[xp];
        } else {
            parent[yp] = xp;
            size[xp] += size[yp];
        }
    }

    int countComponents(int n, vector<vector<int>>& edges) {
        parent.resize(n);
        size.resize(n, 1);

        for(int i = 0; i < n; i++) parent[i] = i;

        int count = n;

        for(auto &e: edges) {
            int xp = FindParent(e[0]);
            int yp = FindParent(e[1]);

            if(xp != yp) {
                merge(xp, yp);
                count--;
            }
        }

        return count;
    }
};
