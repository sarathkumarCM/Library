#include<bits/stdc++.h>

using namespace std;
class Solution {
public:
    bool place(int r, int c){
        for(int prev=0;prev<c;prev++){
            if(row[prev]==r || (abs(row[prev]-r)==abs(prev-c))){
                return false;
            }
        }
        return true;
    }
    void backTrack(int c, vector<vector<int>> &res, int n){
        if(c==n){
            //filled in 
            vector<int> rn=row;
            res.push_back(rn);
        }
        for(int r=0;r<n;r++){
            if(place(r,c)){
                row[c]=r;
                backTrack(c+1,res,n);
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        if(n==0){
            return {{}};
        }
        else if(n==1){
            return {{"Q"}};
        }
        row.assign(n,0);
        vector<vector<int>> res;
        
        backTrack(0,res,n);
        vector<vector<string>> ans(res.size(), vector<string> (n,string(n,'.')));
        //ans[0][0]='Q';
        for(int i=0;i<res.size();i++){
            for(int j=0;j<res[i].size();j++){
                //cerr<<"row "<<n-1-res[i][j]<<endl;
                ans[i][n-1-res[i][j]][j]='Q';
            }
        }
        // for(auto &it:res){
        //     for(auto &it2: it){
        //         cerr<<" "<<it2;
        //     }
        //     cerr<<endl;
        // }

        return ans;
    }
    vector<int> row;
};

int main(){
    int n;
    cin>>n;
    Solution s;
    vector<vector<string>> ans=s.solveNQueens(n);
    for(auto &it: ans){
        for(auto &it2:it){
            cerr<<it2<<endl;
        }
        cerr<<endl<<endl;
    }
}

class Solution2 {
public:
    int count = 0;

    void solve(int row, int n, vector<int>& col, vector<int>& diag1, vector<int>& diag2) {
        if (row == n) {
            count++;
            return;
        }

        for (int c = 0; c < n; c++) {
            // Check if placing queen is safe
            if (col[c] == 0 && diag1[row + c] == 0 && diag2[row - c + n - 1] == 0) {
                
                // Place queen
                col[c] = 1;
                diag1[row + c] = 1;
                diag2[row - c + n - 1] = 1;

                solve(row + 1, n, col, diag1, diag2);

                // Backtrack
                col[c] = 0;
                diag1[row + c] = 0;
                diag2[row - c + n - 1] = 0;
            }
        }
    }

    int totalNQueens(int n) {
        vector<int> col(n, 0);
        vector<int> diag1(2 * n - 1, 0);       // row + col
        vector<int> diag2(2 * n - 1, 0);       // row - col + (n-1)

        solve(0, n, col, diag1, diag2);
        return count;
    }
};


// best
bool isSafe(int row , int col, vector<string> &board ,int n){
    int drow = row;
    int dcol = col;

    //lower diagonal
    while(row>=0 && col >=0){
        if(board[row][col]=='Q') return false;
        row--;
        col--;
    }


    row = drow;
    col = dcol;

    //prev ccols
    while(col>=0){
        if(board[row][col]=='Q') return false;
        col--;
    }

    col = dcol;

    //upper diagonal
    while(col>=0 && row <n){
        if(board[row][col]== 'Q') return false;
        row++;
        col--;

    }

    return true;

}


void sol(int col , vector<string> &board , vector<vector<string>> &ans , int n){

if(col == n){
    ans.push_back(board);
    return;
}


    for(int row = 0 ; row<n ; row++){
        if(isSafe(row , col , board , n)){
            board[row][col] = 'Q';
            sol(col+1 , board , ans , n);
            board[row][col] = '.';

        }
    }


    
}


class Solution3 {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string>  board(n , string(n , '.'));
        
        vector<vector<string>> ans;
        sol(0 , board , ans , n);


        return ans;
    }
};