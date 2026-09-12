class Solution {
    struct Node {
        long long sum = 0;
        array<int, 4> id = {0, 0, 0, 0};
        int cnt = 0;
    };

    bool better(const Node& a, const Node& b) {
        if (a.sum != b.sum) return a.sum > b.sum;

        int n = min(a.cnt, b.cnt);

        for (int i = 0; i < n; i++) {
            if (a.id[i] != b.id[i])
                return a.id[i] < b.id[i];
        }

        return a.cnt < b.cnt;
    }

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<int, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {intervals[i][0], intervals[i][1],
                    intervals[i][2], i};
        }

        sort(a.begin(), a.end());

        vector<int> next(n);

        for (int i = 0; i < n; i++) {
            int l = i + 1, r = n;

            while (l < r) {
                int m = l + (r - l) / 2;

                if (a[m][0] > a[i][1])
                    r = m;
                else
                    l = m + 1;
            }

            next[i] = l;
        }

        vector<Node> dp[5];

        for (int k = 0; k <= 4; k++)
            dp[k].resize(n + 1);

        for (int k = 1; k <= 4; k++) {
            for (int i = n - 1; i >= 0; i--) {
                dp[k][i] = dp[k][i + 1];

                Node take = dp[k - 1][next[i]];

                take.sum += a[i][2];

                for (int j = take.cnt; j > 0; j--)
                    take.id[j] = take.id[j - 1];

                take.id[0] = a[i][3];
                take.cnt++;

                sort(take.id.begin(), take.id.begin() + take.cnt);

                if (better(take, dp[k][i]))
                    dp[k][i] = take;
            }
        }

        vector<int> ans;

        for (int i = 0; i < dp[4][0].cnt; i++)
            ans.push_back(dp[4][0].id[i]);

        return ans;
    }
};