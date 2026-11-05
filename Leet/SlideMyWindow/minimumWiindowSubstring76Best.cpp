#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> freq(128, 0);

        // Store frequency of characters in t
        for (char c : t) freq[c]++;

        int left = 0, count = t.size();
        int minLen = INT_MAX, start = 0;

        for (int right = 0; right < s.size(); right++) {
            // If char is needed, decrease count. cabwefgewcwaefgcf cae
            if (freq[s[right]] > 0) count--;
            freq[s[right]]--;

            // When all chars matched
            while (count == 0) {
                // Update minimum window
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    start = left;
                }

                // Try to shrink window
                freq[s[left]]++;
                if (freq[s[left]] > 0) count++;
                left++;
            }
        }

        return minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};