class Solution {
public:
    vector<string> braceExpansionII(string expr) {
        int i = 0;
        set<string> res = parseExpr(expr, i);
        return vector<string>(res.begin(), res.end());
    }

private:
    set<string> parseExpr(const string& s, int& i) {
        set<string> res = parseTerm(s, i);
        while (i < (int)s.size() && s[i] == ',') {
            i++; // skip ','
            set<string> t = parseTerm(s, i);
            res.insert(t.begin(), t.end());
        }
        return res;
    }

    set<string> parseTerm(const string& s, int& i) {
        set<string> res = {""};
        while (i < (int)s.size() && s[i] != ',' && s[i] != '}') {
            set<string> f = parseFactor(s, i);
            set<string> newRes;
            for (const string& a : res)
                for (const string& b : f)
                    newRes.insert(a + b);
            res = newRes;
        }
        return res;
    }

    set<string> parseFactor(const string& s, int& i) {
        if (s[i] == '{') {
            i++; // skip '{'
            set<string> r = parseExpr(s, i);
            i++; // skip '}'
            return r;
        } else {
            int j = i;
            while (j < (int)s.size() && islower(s[j])) j++;
            set<string> r = {s.substr(i, j - i)};
            i = j;
            return r;
        }
    }
};