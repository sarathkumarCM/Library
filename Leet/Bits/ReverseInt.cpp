#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        int res=0;
        while(x!=0){
            int lb=x%10;
            if(res>(INT_MAX/10) || res<(INT_MIN/10)) return 0;
            if(res==(INT_MAX/10) && lb > (INT_MAX%10)) return 0;
            if(res==INT_MIN/10 && lb <(INT_MIN%10)) return 0;
            res=res*10+lb;
            x/=10;
        }
        return res;
    }
};

//best

class Solution {
public:
    int reverse(int x) {
        int max = 2147483647;
        int min = -2147483648;

        int res = 0;
        while(x != 0)
        {
            int digit = x % 10;
            x /= 10;

            if(res > max/10 || (res == max/10 && digit > max%10)) return 0;
            if(res < min/10 || (res == min/10 && digit < min%10)) return 0;
            res = (res * 10) + digit;
        }

        return res;
    }
};


//also
class Solution {
   public:
    int reverse(int x) {
        int ans = 0;
        while (x != 0) {
            int digit = x % 10;
            if (ans > INT_MAX / 10 || ans < INT_MIN / 10) return 0;
            ans = ans * 10 + digit;
            x = x / 10;
        }
        return ans;
    }
};
