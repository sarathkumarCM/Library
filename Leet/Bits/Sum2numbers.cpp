#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    // a ^ b -> result of all bits sum except for carry (sum except for 1 & 1)
    // a & b -> result of all bits carries (only 1 & 1 carry)
    //easy  - return log2(pow(2,a)*pow(2,b)); or 
    int getSum(int a, int b) {
        while(b!=0){
            int c= (a&b)<<1; // this is the carry
            a=a^b;
            b=c;
        }
        return a;
    }
};

// 1010
// 1010
//c=a &b =10 => 1010<<1 = 010. = a^b basically adds 0010 1