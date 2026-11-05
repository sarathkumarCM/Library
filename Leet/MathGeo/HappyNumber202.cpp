#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isHappy(int n) {
        
        while(n!=1 && n!=4){ //n= 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4 special cycle or fo floyds cycle - next and nextNext if its same return
            long long  sm=0;
            while(n){
                int c=n%10;
                sm+=(c*c);
                n/=10;
            }
            n=sm;

        }
        return n==1;
    }
};

//cycle
class Solution {
public:
    int fun(int n) {
        int sum = 0;

        while(n > 0) {
            int d = n%10;
            n = n/10;

            sum = sum + d*d;
        }
        return sum;
    }


    bool isHappy(int n) {
        int slow = n;
        int fast = n;

        while(fast != 1) {
            slow = fun(slow);
            fast = fun(fun(fast));

            
            if(slow == fast && slow != 1) {
                return false;
            }
        }

        return true;
    }
};