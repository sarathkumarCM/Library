#include<bits/stdc++.h>

using namespace std;
class Solution {
public:
    string multiply(string num1, string num2) {
        int m=num1.size(),n=num2.size();
        vector<int> res(m+n,0);
        for(int i=n-1;i>=0;i--){
            for(int j=m-1;j>=0;j--){
                int n1=num2[i]-'0';
                int n2=num1[j]-'0';
                int nm=n1*n2;
                int p=i+j;
                int p2=i+j+1;
                int sum=nm+res[p2];
                res[p]+=sum/10;
                res[p2]=sum%10;
            }
        }
        string ans="";
        for(auto &it:res){
            if(!(ans.empty() && it==0)){
                ans+=it+'0';
            }
        }
        return ans==""?"0":ans;
        
    }
};

int main(){
    string a,b;
    cin>>a>>b;
    Solution ss;
    cout<<ss.multiply(a,b);
}

//Best
class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        int n1 = num1.length(), n2 = num2.length();
        int len = n1 + n2;

        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        string ans(len, '0'); 
        for (int p2 = 0; p2 < n2; ++p2) {
            int d2 = num2[p2] - '0';
            for (int p1 = 0; p1 < n1; ++p1) {
                int d1 = num1[p1] - '0';
                
                int zeros = p1 + p2;
                int carry = ans[zeros] - '0';

                int res = d1 * d2 + carry;

                ans[zeros] = (res % 10) + '0';
                ans[zeros + 1] += (res / 10); //this is char + int
            }
        }
        if (ans.back() == '0') ans.pop_back();
        reverse(ans.begin(), ans.end());

        return ans;
    }
};