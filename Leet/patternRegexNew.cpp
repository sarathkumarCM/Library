#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int sl=s.length(),pl=p.length();
        for(int i=0,j=0;i<sl;){
            if(j>pl-1){
                return false;
            }
            char cc=p[j];
            cerr<<"Pattern at: "<<cc<<endl;
            if(cc =='*' && j>0 ){
                char prev=p[j-1];
                cerr<<"\tPrev char: "<<prev<<endl;
                if(prev=='.'){
                    return true;
                }
                while(i<sl && prev==s[i]){
                    i++;
                }
                cerr<<"\tS is at : "<<s[i]<<endl;
                j++;

            }else if(cc=='.'){
                if(j==pl-1){
                    i++; 
                    j++;
                    continue;
                }
                char nxt=p[j+1];
                 cerr<<"\next char:"<<nxt<<endl;
                if(nxt=='*') return true;
                j++;
                i++;

            }else if(cc!='*'){
                if(j==pl-1){
                    if(i!=sl-1) return false;
                    if(s[i]!=p[j]) return false;
                    i++;
                    j++;
                }
                if(s[i]!=p[j]) return false;
                char nxt=p[j+1];
                if(nxt!='*'){
                    if(s[i]!=p[j]) return false;
                }
                cerr<<"\tNext char: "<<nxt<<endl;
                cerr<<"S & P: "<<s[i]<<p[j]<<endl;
                i++;
                j++;
            }
        }
        return true;
    }

    bool isMatch(string s, string p, int ppess) {
        int sl=s.length(),pl=p.length(); //j for pattern i for string
        int i=0,j=0;
        for(;i<sl;){
            if(j>pl-1){
                return false;
            }
            char pp=p[j];
            char pn=(j>=pl-1)?'-':p[j+1];
            cerr<<"Pattern at: "<<pp<<endl;
            if(pn!='-'){
                if(pn=='*'){ // next is * so skip or move so much
                    if(pp=='.'){
                        
                        //if .* after that nothing then omit
                        if(j==pl-2)
                            return true;
                        j+=2;
                        int ti=sl-1;
                        // while(ti<)

                    }else{
                        cerr<<"\tstring char: "<<s[i]<<endl;
                        while(i<sl && p[j]==s[i]){
                            i++; // wierd case occurs if s*s occurs
                        }
                        char oldChar=p[j];
                        j+=2;// skip past the *
                        while(oldChar==p[j]) j++; // wierd case handled
                    }
                    
                }else{
                    if(p[j]=='.') { // next is not *
                        i++;j++;
                    }
                    else if(s[i]!=p[j]) { cerr<<"\t\tThrown error?";return false; }//not matching
                    else{
                        
                        while((i<sl && j<pl) && s[i]==p[j]){
                            if(j<pl-1 && p[j+1]=='*'){
                                break;
                            }
                            i++;j++;
                        }
                    }
                }

            }else{
                cerr<<"\t bs: "<<endl;
                cerr<<"\tPattern at :"<<pp<<" string at: "<<s[i]<<endl;
                cerr<<"\t\t I & j "<<i<<" "<<j<<endl;
                //last pattern char obv not a *
                if(pp=='.'){
                    i++;j++;
                }
                else if(s[i]!=pp) return false; // non matching
                i++;
                j++;
                if(i<sl) {cerr<<"Error here? ";return false;} //not the end of actual string
                if(s[i]==pp) return true;

            }


        }
        if(j<pl)
            return false;
        return true;
    }
};

int main(){

    Solution sol;
    string s,p;
    cin>>s>>p;
    auto ans=sol.isMatch(s,p,0);
    cout<<ans<<endl;
}