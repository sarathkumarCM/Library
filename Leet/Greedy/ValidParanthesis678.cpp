#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkValidString(string s) {
        stack<int> inp,star;
        for(int i=0;i<s.size();i++){
            if(s[i]=='('){
                inp.push(i);
            }else if(s[i]=='*'){
                star.push(i);
            }else{
                //pop
                if(!inp.empty()){
                    inp.pop();
                }else if(!star.empty()){
                    star.pop();
                }
                else{
                    return false; //special case
                }
            }
        }
        if(inp.size()>star.size()){
            return false;
        }
        while(!inp.empty() && !star.empty()){
            int l=inp.top();
            int r=star.top();
            if(l>r){
                return false;
            }
            inp.pop();
            star.pop();
        }
        return true;

    }
};

int main(){
    string s;
    cin>>s;
    Solution ss;
    cout<<ss.checkValidString(s);

}

//best -- smart a f
class Solution {
public:
    bool checkValidString(string s) {
        int min=0,max=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='('){
                min++;
                max++;
            }
            else if(s[i]==')'){
                min--;
                max--;
            }
            else{
                min--;
                max++;
            }
            if(min<0) min=0;
            if(max<0) return false;
        }
        return min==0;
    }
};