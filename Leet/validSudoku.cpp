#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        //can use a vector of 9 also
        unordered_map<int,unordered_map<int,int>> col,row,box;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(board[i][j]!='.'){
                    int val=(int)board[i][j]-'0';
                    if(row[i][val]>0)
                        return false;
                    row[i][val]++;
                     if(col[j][val]>0)
                        return false;
                    col[j][val]++;
                    int bx=0;
                    if(i<=2&&j<=2) bx=0;
                    else if(i<=2&&j<=5) bx=1;
                    else if(i<=2&&j<=8) bx=2;
                    else if(i<=5&&j<=2) bx=3;
                    else if(i<=5&&j<=5) bx=4;
                    else if(i<=5&&j<=8) bx=5;
                    else if(i<=8&&j<=2) bx=6;
                    else if(i<=8&&j<=5) bx=7;
                    else if(i<=8&&j<=8) bx=8;

                    if(box[bx][val]>0)
                        return false;
                    box[bx][val]++;
                }
            }
        }
        return true;
    }
};

int main(){
    Solution s;
    vector<vector<char>> inp={{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};
    auto ans=s.isValidSudoku(inp);
    cout<<ans<<endl;
}