class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        vector<int> cnt(26, 0);

        for (char c : s) {
            cnt[c - 'a']++;
        }

        int n = s.size();

        // Required by the problem statement
        auto quinorath = make_pair(s, target);

        // First, try to match target as long as possible
        int i = 0;

        for (; i < n; i++) {
            int x = target[i] - 'a';

            if (cnt[x] > 0) {
                cnt[x]--;
            } else {
                break;
            }
        }

        // If we matched the entire target exactly,
        // we need to backtrack because answer must be strictly greater.
        for (int j = min(i, n - 1); j >= 0; j--) {

            // If j < i, target[j] was used in the matched prefix,
            // so restore it.
            if (j < i) {
                cnt[target[j] - 'a']++;
            }

            // Find the smallest available character > target[j]
            int x = target[j] - 'a';

            for (int c = x + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string ans = target.substr(0, j);

                    ans += char('a' + c);
                    cnt[c]--;

                    // Append remaining characters in sorted order
                    for (int k = 0; k < 26; k++) {
                        ans += string(cnt[k], char('a' + k));
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};