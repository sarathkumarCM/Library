#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
     int reverseBits(int n) {
        u_int32_t mask=1;
        u_int32_t res=0;
       for (auto i = 0; i < 32; i++) {
            res=(res<<1) | (n&mask);
            n=n>>1;
        }
        return res;
    }
};