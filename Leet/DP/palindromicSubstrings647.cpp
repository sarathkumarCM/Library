#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countSubstrings(string s) {
        int n=s.size();
        int pals=0;
        int prev,next;
        for(int i=1;i<n;i++){
            int prev=i-1;
            int next=i+1;
            
            while(true){
                if(prev<0){
                    prev++;
                    break;
                }
                if(next>n-1){
                    next--;
                    break;
                }
                if(s[prev]!=s[next]){
                    prev++;
                    next--;
                    break;
                }
                prev--;
                next++;
                pals++;

            }
        }
        int L,R;
        int pal2=0;
        for(int i=0;i+1<n;i++){
            int L=i;
            int R=i+1;
            while(true){
                if(L<0){
                    L++;
                    break;
                }
                if(R>n-1){
                    R--;
                    break;
                }
                if(s[L]!=s[R]){
                    L++;
                    R--;
                    break;
                }
                L--;
                R++;
                pal2++;

            }
        }
        //cerr<<"pal1: "<<pals<<" , pal2: "<<pal2<<endl;
        return pal2+pals+s.size();
        
    }
};

int main(){
    string s;
    cin>>s;
    Solution ss;
    cout<<ss.countSubstrings(s);
}

//best
class Solution {
public:
    int expand(string & s, int left, int right) {
        int cnt = 0;
        while(left >= 0 && right < s.length() && s[left] == s[right]) {
            ++cnt;
            --left;
            ++right;
        }
        return cnt;
    }

    int countSubstrings(string s) {
        int cnt = 0;
        for(int i = 0; i < s.length(); ++i) {
            cnt += expand(s, i, i);
            cnt += expand(s, i, i+1);
        }
        return cnt;
    }
};