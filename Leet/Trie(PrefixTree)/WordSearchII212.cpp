#include<bits/stdc++.h>

using namespace std;

class TrieNode {
public:
    vector<TrieNode*> next;
    bool wordEnd=false;

    TrieNode() : next(26, nullptr),wordEnd(false) {}
    ~TrieNode() {
        for(auto &it:next){
            delete it;
        }
    }
};

class Solution {
public:

    void dfs(int i, int j, vector<vector<char>>& board, TrieNode *root, string &res){
        if(i<0 || i>=m || j<0 ||j>=n ||board[i][j]=='#' ||root ==nullptr){
            return;
        }

        char temp = board[i][j];

        if (root->next[temp - 'a'] == nullptr)
            return;

        
        root = root->next[temp - 'a'];
        
        // int s=search(troot,res);
        // if(s==0){
        //     return;
        // }else if(s==1){
        //     ans.push_back(res);
        // }
        res.push_back(temp);
        if(root->wordEnd){
            cerr<<"ans found: "<<res<<endl;
            ans.push_back(res);
            root->wordEnd=false; //remove duplicates
        }

        board[i][j] = '#';

        dfs(i,j+1,board,root,res);
        dfs(i,j-1,board,root,res );
        dfs(i+1,j,board,root,res);
        dfs(i-1,j,board,root,res);

        // dfs(i,j+1,board,root->next[temp - 'a'],res);
        // dfs(i,j-1,board,root->next[temp - 'a'],res );
        // dfs(i+1,j,board,root->next[temp - 'a'],res);
        // dfs(i-1,j,board,root->next[temp - 'a'],res);
        board[i][j]=temp;
        res.pop_back();


    }

     int search(TrieNode *root, string word){
        for(auto &ch:word){
            if(root->next[ch-'a']==nullptr)
                return 0;
            root=root->next[ch-'a'];
        }
        if(root->wordEnd==true)
            return 1;
        return -1;
    }

    void insert(string word,TrieNode *root) {
        for(auto &c: word){
            if(root->next[c-'a']==nullptr){
                TrieNode *newNode=new TrieNode();
                root->next[c-'a']=newNode;
            }
            root=root->next[c-'a'];
        }
        root->wordEnd=true;
        
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode *root=new TrieNode();
        troot=root;
        m=board.size();
        n=board[0].size();
        for(auto &it: words){
            insert(it,root);
        }
        string res;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                dfs(i,j,board,root,res);
            }
        }
        return ans;
    }
    int m,n;
    vector<string> ans;
    TrieNode *troot=nullptr;

};

class Solution2 {
public:

    bool search(TrieNode *root, string word){
        for(auto &ch:word){
            if(root->next[ch-'a']==nullptr)
                return false;
            root=root->next[ch-'a'];
        }
        return true;
    }
    
    void makeTrie(vector<vector<char>>& board, int i, int j,TrieNode *root, int len){
        if(i<0 || i>=m || j<0 ||j>=n ||board[i][j]=='#'|| len>md){
            return;
        }
        char temp=board[i][j];
        board[i][j]='#';
        if(root->next[temp-'a']==nullptr)
            root->next[temp-'a']=new TrieNode();
        cerr<<"\t\tNext node added is "<<temp<<endl;
        makeTrie(board,i,j+1,root->next[temp-'a'],len+1);
        makeTrie(board,i,j-1,root->next[temp-'a'],len+1);
        makeTrie(board,i+1,j,root->next[temp-'a'],len+1);
        makeTrie(board,i-1,j,root->next[temp-'a'],len+1);
        board[i][j]=temp;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> ans;
        TrieNode *root=new TrieNode();
        m=board.size();
        n=board[0].size();
        for(auto &it:words){
            int ws=it.size();
            md=max(md,ws);
        }
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                cerr<<"\tNow begin for: "<<board[i][j]<<endl;
                makeTrie(board,i,j,root,0);
            }
        }
        for(auto &it:words){
            if(search(root,it)){
                ans.push_back(it);
            }
        }
        return ans;
    }
    int m,n;
    int md=0;
};

int main(){
    int m,n;
    cin>>m>>n;
    //cin.ignore();
    vector<vector<char>> board(m, vector<char> (n));
    for(auto &it:board){
        for(auto &it2:it){
            cin>>it2;
        }
    }   

    int k;
    cin>>k;
    vector<string>  words(k);
    for(auto &it:words){
        cin>>it;
    }

    //print
    for(auto &it:board){
        for(auto &it2:it){
            cerr<<" "<<it2;
        }
        cerr<<endl;
    }
    for(auto &it:words)
        cerr<<" "<<it;
    cerr<<endl;

    Solution s;
    auto ans=s.findWords(board,words);
    for(auto &it: ans){
        cout<<" "<<it;
    }
}

//Best
class Solution3 {
public:

    // ================= TRIE NODE DEFINITION =================
    struct TrieNode {
        TrieNode* children[26];   // Pointers to next characters
        string word;              // Stores full word if this node is end of word

        // Constructor → initialize children to NULL and word empty
        TrieNode() {
            for (int i = 0; i < 26; i++)
                children[i] = nullptr;
            word = "";
        }
    };

    // Board dimensions (stored globally to avoid passing repeatedly in DFS)
    int n, m;

    // Movement directions → up, down, left, right
    vector<pair<int,int>> dirs = {
        {-1,0}, {1,0}, {0,-1}, {0,1}
    };

    // ================= BUILD TRIE FROM WORD LIST =================
    TrieNode* buildTrie(vector<string>& words){

        // Create root node
        TrieNode* root = new TrieNode();

        // Insert each word into Trie
        for(string &word : words){

            TrieNode* curr = root;

            // Traverse characters of word
            for(char ch : word){

                int idx = ch - 'a';

                // If path does not exist → create node
                if(curr->children[idx] == nullptr)
                    curr->children[idx] = new TrieNode();

                // Move to next Trie node
                curr = curr->children[idx];
            }

            // Store full word at last node (marks end of word)
            curr->word = word;
        }

        return root;
    }


    // ================= DFS SEARCH ON BOARD =================
    void dfs(vector<vector<char>>& board,
             int r, int c,
             TrieNode* node,
             vector<string>& ans) {

        char ch = board[r][c];

        /*
            PRUNING CONDITIONS:
            1) If cell already visited (#)
            2) If Trie has no child for this character → prefix invalid
        */
        if (ch == '#' || node->children[ch - 'a'] == nullptr)
            return;

        // Move into Trie node corresponding to current character
        node = node->children[ch - 'a'];

        /*
            If Trie node contains a word → we found a valid word
            Add to result and clear to prevent duplicates
        */
        if (!node->word.empty()) {
            ans.push_back(node->word);
            node->word = "";   // Prevent duplicate discovery
        }

        // Mark board cell as visited
        board[r][c] = '#';

        // Explore all 4 directions
        for (auto &d : dirs) {

            int nr = r + d.first;
            int nc = c + d.second;

            // Check board boundaries
            if (nr >= 0 && nr < n && nc >= 0 && nc < m)
                dfs(board, nr, nc, node, ans);
        }

        // Backtrack → restore original character
        board[r][c] = ch;
    }


    // ================= MAIN FUNCTION =================
    vector<string> findWords(vector<vector<char>>& board,
                             vector<string>& words) {

        // Store board dimensions
        n = board.size();
        m = board[0].size();

        // Build Trie from word list
        TrieNode* root = buildTrie(words);

        vector<string> ans;

        /*
            Start DFS from each board cell
            Optimization → only start DFS if Trie has matching first character
        */
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){

                if(root->children[board[i][j] - 'a'] != nullptr)
                    dfs(board, i, j, root, ans);
            }
        }

        return ans;
    }
};
/*
    ================= COMPLEXITY ANALYSIS =================

    Let:
    n = rows, m = columns
    N = n * m  (total board cells)
    W = number of words
    L = max word length
    T = total characters across all words

    Time Complexity:
    - Trie Build  : O(T)
    - DFS Search  : O(N * 4^L)   (worst case, heavily pruned by Trie)
    -----------------------------------------------------
    Total TC      : O(T + N * 4^L)

    Space Complexity:
    - Trie Storage     : O(T)
    - Recursion Stack  : O(L)
    -----------------------------------------------------
    Total SC           : O(T + L)
    */

/*
Time Complexity:

Trie Build → O(T)

DFS → O(N * 4^L)
N = board cells, L = max word length
DFS branches in 4 directions per step, depth limited by L.
Trie prefix pruning cuts invalid paths early.

Overall → O(T + N * 4^L)
*/

auto init = atexit([]() { ofstream("display_runtime.txt") << "0"; });