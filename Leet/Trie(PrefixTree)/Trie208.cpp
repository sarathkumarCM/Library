#include <bits/stdc++.h>
using namespace std;

class Trie {
public:
    Trie() {
        wordEnd=false;
        next.clear();
    }
    
    void insert(string word) {
        Trie *root=this;
        for(auto &c: word){
            if(root->next.find(c)==root->next.end()){
                Trie *newNode=new Trie();
                root->next[c]=newNode;
            }
            root=root->next[c];
        }
        root->wordEnd=true;
        
    }
    
    bool search(string word) {
        Trie *root=this;
        for(auto &c:word){
            if(root->next.find(c)==root->next.end()){
                return false;
            }
            root=root->next[c];
        }
        if(root->wordEnd==true)
            return true;
        return false;   
    }
    
    bool startsWith(string prefix) {
        Trie *root=this;
        for(auto &c:prefix){
            if(root->next.find(c)==root->next.end()){
                return false;
            }
            root=root->next[c];
        }
        return true;
    }
    unordered_map<char,Trie *> next;
    bool wordEnd=false;
};


int main(){
    int n;
    cin>>n;
    Trie *root;
    while(n--){
        string a;
        cin>>a;
        if(a=="Trie"){
            root=new Trie();
            cout<<" null ";
        }else if(a=="insert"){
            cin>>a;
            root->insert(a);
            cout<<" null"<<" ";
        }else if(a=="search"){
            cin>>a;
            cout<<" "<<root->search(a);
        }else{
            cin>>a;
            cout<<" "<<root->startsWith(a);
        }
    }

}

//Best use an array of 26 for and set it 
class Trie2 {
private:
    struct TrieNode {
        TrieNode* children[26];
        bool isEnd;

        TrieNode() {
            isEnd = false;
            for (int i = 0; i < 26; i++)
                children[i] = nullptr;
        }
    };

    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx])
                return false;
            node = node->children[idx];
        }
        return node->isEnd;
    }

    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx])
                return false;
            node = node->children[idx];
        }
        return true;
    }
};