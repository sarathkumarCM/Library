#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int hammingWeight(int n) {
        return __builtin_popcount(n); //can do &1 bit by bit and then shift
    }
};

//another
int hammingWeight(int n) {
       int cnt=0;
       while(n>0){
         n=n&(n-1);
         cnt++;
       }
       return cnt;
    }

     int hammingWeight2(int n) {
        uint32_t mask = 1;
        uint8_t cnt = 0;
        for (auto i = 0; i < 32; i++) {
            if (n & mask)
                cnt++;
            mask <<= 1;
        }
        return cnt;
    }