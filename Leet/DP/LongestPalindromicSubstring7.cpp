#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int n=s.size();
        int i=0,prev=-1,next=1;
        string longest={s[0]};//+s[0];
        int longLen=0;
        for(int i=1;i<n;i++){
            int prev=i-1;
            int next=i+1;
            if(prev<0) continue;
            if(next>=n) continue;
            while(true){
                if(s[prev]!=s[next]) { 
                    prev++;
                    next--;
                    break;
                }
                if(prev==0) break;
                if(next==n-1) break;
                prev--;
                next++;
            }
            if((next-prev+1) > longLen){
                longLen=next-prev+1;
                //cerr<<"prev :"<<prev<<" , longlen:"<<longLen<<endl;
                longest=s.substr(prev,longLen);
            }
        }
        string l2="";
        int l2l=0;

        if(n>1){
            int l=0,r=1;
            for(i=0;i+1<n;i++){
                l=i;
                r=i+1;
                while(true){
                    if(s[l]!=s[r]){
                        l++;
                        r--;
                        break;
                    }
                    if(l<=0) break;
                    if(r>=n-1) break;
                    l--;
                    r++;
                }
                if(l<0)continue;
                if(r>n-1) continue;
                if(l<r && (r-l+1)>l2l){
                    l2l=r-l+1;
                    //cerr<<"L :"<<l<<" , R:"<<r<<" longlen2: "<<l2l<<endl;
                    l2=s.substr(l,l2l);
                }

            }
        }
        if(l2l>longLen){
            longest=l2;
        }

        return longest;
    }
};

int main(){
    string s;
    cin>>s;
    Solution ss;
    cout<<ss.longestPalindrome(s);
}

//best
class Solution {
public:
    string longestPalindrome(string t) {
        string s = "#";
        int m = t.length();
        for (int i = 0; i < m; i++) {
            s += t[i];
            s += '#';
        }
        int n = s.length(), center = 0, right = 0;
        vector<int> p(n, 0);
        for (int i = 0; i < n; i++) {
            int mirror = 2 * center - i;
            if (i < right) {
                p[i] = min(right - i, p[mirror]);
            }
            while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n &&
                   s[i - p[i] - 1] == s[i + p[i] + 1]) {
                p[i]++;
            }
            if (p[i] + i > right) {
                center = i;
                right = i + p[i];
            }
        }
        int maxIndex = 0;
        for (int i = 0; i < n; i++) {
            if (p[maxIndex] < p[i]) {
                maxIndex = i;
            }
        }
        return t.substr((maxIndex - p[maxIndex]) / 2, p[maxIndex]);
    }
};

// another easier to code

class Solution {
public:
    int cntPal(string s, int n) {
    int cnt = 0;
    for (int mid = 0; mid < n; ++mid) {
        for (int l = mid, r = mid; l >= 0 && r < n; --l, r++) {
            if (s[l] == s[r]) cnt++;
            else break;
        }
        for (int l = mid, r = mid + 1; l >= 0 && r < n; --l, r++) {
            if (s[l] == s[r]) cnt++;
            else break;
        }
    }
    return cnt;
}
    int countSubstrings(string s) {
        int n = s.size();
        return cntPal(s, n);
    }
};