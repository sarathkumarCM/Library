#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool backTrack(int i, int j,int nchar, string word,int m, int n,vector<vector<char>> &board,vector<vector<bool>> &visited){
        
        if(nchar==word.size()){
            cerr<<"found"<<endl;
            return true;
        }

        if(i<0 ||i >=m ||j<0|| j>=n){
            cerr<<"Out of bounds"<<endl;
            return false;
        }
        cerr<<"Currently at ("<<i<< ","<<j<<"), char nums: "<<nchar<<" , board[i][j]: "<<board[i][j]<<" word[nchar] " <<word[nchar]<<endl;
        if(word[nchar]!=board[i][j]){
            return false;
        }
        if(nchar==word.size()-1)
            return true;
        visited[i][j]=true;
        bool a1=false, a2=false, a3=false, a4=false;
        if((i+1)< m && !visited[i+1][j]){
            a1=backTrack(i+1,j,(nchar+1),word,m,n,board,visited);
            if(a1==true)
                return true;
            visited[i+1][j]=false;
        }
        if((j+1)<n && !visited[i][j+1]){
            a2=backTrack(i,j+1,(nchar+1),word,m,n,board,visited);
            if(a2==true)
                return true;
            visited[i][j+1]=false;
        }
        if((i-1)>=0 && !visited[i-1][j]){
            a3=backTrack(i-1,j,(nchar+1),word,m,n,board,visited);
            if(a3==true)
                return true;
            visited[i-1][j]=false;
        }
        if((j-1)>=0 && !visited[i][j-1]){
            a4=backTrack(i,j-1,(nchar+1),word,m,n,board,visited);
            if(a4==true)
                return true;
            visited[i][j-1]=false;
        }
        return a1 || a2 || a3 ||a4;

            
    }
    bool exist(vector<vector<char>>& board, string word) {
        char ch=word[0];
        string cWord=to_string(word[0]);
        for(int k=0;k<word.size();k++){
            bool found=false;
            for(int i=0;i<board.size();i++){
                for(int j=0;j<board[i].size();j++){
                    if(word[k]==board[i][j]){
                        found=true;
                        break;
                    }
                }
                if(found)
                    break;
            }
            if(!found)
                return false;
        }

        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                if(board[i][j]==ch){
                    vector<vector<bool>> visited(board.size(),vector<bool> (board[0].size(),false));
                    bool found= backTrack(i,j,0,word,board.size(),board[i].size(),board,visited);
                    if(found)
                        return true;
                }
            }
        }
        return false;
    }
};

int main(){
    int m,n;
    cin>>m>>n;
    vector<vector<char>> inp(m, vector<char> (n));
    for(auto &it:inp){
        for (auto &it2: it){
            cin>>it2;
        }
    }   
    string word;
    cin>>word;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cerr<<inp[i][j]<<" ";
        }
        cerr<<endl;
    }
    Solution s;
    cout<<s.exist(inp,word);
}

//okok

//Best
class Solution {
public:
    int m, n;

    bool solve(int i, int j, int idx, vector<vector<char>>& board, string& word) {
        if(idx == word.size()) return true;

        if(i < 0 || j < 0 || i >= m || j >= n || board[i][j] != word[idx])
            return false;

        char temp = board[i][j];
        board[i][j] = '#';

        bool found = solve(i+1, j, idx+1, board, word) ||
                     solve(i-1, j, idx+1, board, word) ||
                     solve(i, j+1, idx+1, board, word) ||
                     solve(i, j-1, idx+1, board, word);

        board[i][j] = temp;

        return found;
    }

    bool exist(vector<vector<char>>& board, string word) {
        m = board.size();
        n = board[0].size();

        vector<int> freq(128, 0);

        for(auto& row : board)
            for(char c : row)
                freq[c]++;

        for(char c : word)
            if(--freq[c] < 0)
                return false;

        if(freq[word[0]] > freq[word.back()]) // to start from rarer char to reduce branching woowwiee
            reverse(word.begin(), word.end());

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(board[i][j] == word[0]){
                    if(solve(i, j, 0, board, word))
                        return true;
                }
            }
        }

        return false;
    }
};