#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int sl=s.length(),pl=p.length();
        for(int i=0,j=0;i<sl;){
            if(p[j]=='*' && j+1==pl){
                return true;
            }
            else if(p[j]=='*'){
                char temp=p[j+1];
                if(temp=='.' || temp=='*'){
                    j++;
                    continue;
                }
                bool f=false;;
                while(i<sl){
                    if(s[i]==temp){
                        j++;
                        f=true;
                        break;
                    }
                    else{
                        i++;
                    }     
                }
                if(!f)
                    return false;
            }
            else if(p[j]=='.'){
                i++;j++;
            }
            else{
                if(s[i]!=p[j])
                    return false;
                i++,j++;
                
            }
        }
        return false;
    }
};

int main(){

    Solution sol;
    string s,p;
    cin>>s>>p;
    auto ans=sol.isMatch(s,p);
    cout<<ans<<endl;
}