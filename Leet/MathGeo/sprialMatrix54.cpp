#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};
    int M,N;
    void dfs(int i,int j,vector<vector<int>> &matrix,vector<vector<bool>> &vis,vector<int> &res){
        if(vis[i][j]) return;
        vis[i][j]=true;
        res.push_back(matrix[i][j]);
        for(auto &it:dirs){
            int di=i+it[0],dj=j+it[1];
            if(min(di,dj)<0 || di>M-1 ||dj>N-1 || vis[di][dj]) continue;
            dfs(di,dj,matrix,vis,res);
            break;
        }
    }
    vector<int> spiralOrder2(vector<vector<int>>& matrix) {
        int m=matrix.size(),n=matrix[0].size();
        M=m,N=n;
        vector<vector<bool>> vis(m,vector<bool>(n,false));
        vector<int> res;
        dfs(0,0,matrix,vis,res);
        return res;
    }

    enum DIR{
        RIGHT=0,DOWN,LEFT,UP
    };
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m=matrix.size(),n=matrix[0].size();
        M=m,N=n;
        vector<vector<bool>> vis(m,vector<bool>(n,false));
        vector<int> res;
        int i=0,j=0;
        DIR cur=RIGHT;
        int nl=0,mt=1;
        while(true){
            //cerr<<"i: "<<i<<", j:"<<j<<endl;
             if(min(i,j)<0 || i>M-1 ||j>N-1 || vis[i][j]) break;
            //if(vis[i][j]) break;
            res.push_back(matrix[i][j]);
            vis[i][j]=true;
            if(cur==RIGHT && j<n-1){
                j++;
            }else if(cur==RIGHT && j==n-1){
                cur=DOWN;
                i++;
            }else if(cur==DOWN && i<m-1){
                i++;
            }else if(cur==DOWN && i==m-1){
                cur=LEFT;
                j--;
                m--;
                n--;
            }else if(cur==LEFT && j>nl){
                j--;
            }else if(cur==LEFT && j==nl){
                cur=UP;
                i--;
                nl++;
                //n--; // can be moved
            }else if(cur==UP&&i>mt){
                i--;
            }else if(cur==UP && i==mt){
                cur=RIGHT;
                j++;
                mt++;
            }
        }
        return res;
    }
};

int main(){
    int m,n;
    cin>>m>>n;
    vector<vector<int>> inp(m, vector<int>(n));
    for(auto &it:inp){
        for(auto &it2:it){
            cin>>it2;
        }
    }
    Solution ss;
    auto res=ss.spiralOrder(inp);
    for(auto &it:res)cout<<it<<" ";
}


//Another 
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m=matrix.size();
        int n=matrix[0].size();
        int srow=0,erow=m-1;
        int scol=0,ecol=n-1;
        vector<int>ans;
        while(srow<=erow && scol<=ecol){
        for(int i=scol;i<=ecol;i++){
            ans.push_back(matrix[srow][i]);
        }
        for(int j=srow+1;j<=erow;j++){
            ans.push_back(matrix[j][ecol]);
        }
        for(int i=ecol-1;i>=scol;i--){
            if(erow==srow){
                break;
            }
            ans.push_back(matrix[erow][i]);
        }
        for(int j=erow-1;j>=srow+1;j--){
            if(ecol==scol){
                break;
            }
            ans.push_back(matrix[j][scol]);
        }
        srow++;
        erow--;
        scol++;
        ecol--;
        }
        return ans;
    }
};

//BEst
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(); int n = matrix[0].size();
        int left =0 , top =0 , bottom = m-1 , right= n-1;
        vector<int> ans;
        while(top<=bottom && left<=right){
            //l2r
            for(int i=left ; i<=right ;i++) ans.push_back(matrix[top][i]);
            top++;
            //t2b
            for(int i=top ; i<=bottom ; i++) ans.push_back(matrix[i][right]);
            right--;
            //r2l
            if(top<=bottom)
            for(int i=right ; i>=left ; i--) ans.push_back(matrix[bottom][i]);
            bottom--;
            //b2t
            if(left<=right)
            for(int i=bottom ; i>=top ; i--) ans.push_back(matrix[i][left]);
            left++;
        }
        return ans;
    }
};