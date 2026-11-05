
#include<bits/stdc++.h>

class Solution {
public:
    double myPowO_N(double x, int n) {
        bool pos=true;
        if(n<0)pos=false,n*=1;
        long double res=x;
        if(n==0) return 1;
        while(n>0){
            res=res*x;
        }
        if(!pos)return (1.0/res);
        return res;

    }

    double myPow(double x, int n) {
       long long N=n;
       if(N<0){
            x=1.0/x;
            N=-N;
       }
       double res=1.0;
       while(N>0){
            if(N&1)
                res*=x;
            x*=x;
            N>>=1;
       }
       return res;

    }
};

//Best
class Solution {
public:
    double recurse(double x, long long n){
        if(n == 0){
            return 1;
        }
        double half = recurse(x, n/2);
        if(n%2 == 0){
            return half*half;
        }
        return x*half*half;
    }

    double myPow(double x, int n) {
        long long N = n;
        if(N < 0){
            x = 1/x;
            N *= -1;
        }
        return recurse(x, N);
    }
};