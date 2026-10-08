class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int l = 0, r = 0;
        for (char c : s) {
            if (c == '(') l++;
            else if (c == ')') {
                if (l > 0) l--;
                else r++;
            }
        }
        vector<string> res;
        dfs(s, 0, l, r, res);
        return res;
    }

private:
    bool isValid(const string& s) {
        int cnt = 0;
        for (char c : s) {
            if (c == '(') cnt++;
            else if (c == ')') {
                if (--cnt < 0) return false;
            }
        }
        return cnt == 0;
    }

    void dfs(string s, int start, int l, int r, vector<string>& res) {
        if (l == 0 && r == 0) {
            if (isValid(s)) res.push_back(s);
            return;
        }
        for (int i = start; i < (int)s.size(); i++) {
            if (i > start && s[i] == s[i - 1]) continue; // skip duplicates
            if (l > 0 && s[i] == '(')
                dfs(s.substr(0, i) + s.substr(i + 1), i, l - 1, r, res);
            if (r > 0 && s[i] == ')')
                dfs(s.substr(0, i) + s.substr(i + 1), i, l, r - 1, res);
        }
    }
};