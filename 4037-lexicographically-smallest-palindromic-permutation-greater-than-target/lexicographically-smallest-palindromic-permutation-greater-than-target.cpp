class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26, 0);

        for (char c : s) {
            cnt[c - 'a']++;
        }

        int odd = 0;
        char middle = 0;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                middle = char('a' + i);
            }
        }

        if (odd > 1) {
            return "";
        }

        vector<int> halfCnt(26);
        for (int i = 0; i < 26; i++) {
            halfCnt[i] = cnt[i] / 2;
        }

        int half = n / 2;
        string prefix;

        auto build = [&]() {
            string left = prefix;

            for (int i = 25; i >= 0; i--) {
                left += string(halfCnt[i], char('a' + i));
            }

            string ans = left;

            if (middle) {
                ans += middle;
            }

            reverse(left.begin(), left.end());
            ans += left;

            return ans;
        };

        for (int pos = 0; pos < half; pos++) {
            bool chosen = false;

            for (int c = 0; c < 26; c++) {
                if (halfCnt[c] == 0) {
                    continue;
                }

                halfCnt[c]--;
                prefix.push_back(char('a' + c));

                string candidate = build();

                if (candidate > target) {
                    chosen = true;
                    break;
                }

                prefix.pop_back();
                halfCnt[c]++;
            }

            if (!chosen) {
                return "";
            }
        }

        string ans = prefix;

        if (middle) {
            ans += middle;
        }

        string rev = prefix;
        reverse(rev.begin(), rev.end());
        ans += rev;

        return ans > target ? ans : "";
    }
};