class Solution {
    struct State {
        long long score = 0;
        vector<int> indices;
        bool done = false;
    };

    vector<array<State, 5>> dp;
    vector<array<int, 4>> a;

    State solve(int i, int k) {
        if (i == a.size() || k == 0)
            return {0, {}, true};

        if (dp[i][k].done)
            return dp[i][k];

        State skip = solve(i + 1, k);

        int r = a[i][1];
        int w = a[i][2];
        int idx = a[i][3];

        int lo = i + 1, hi = a.size();

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (a[mid][0] > r)
                hi = mid;
            else
                lo = mid + 1;
        }

        State next = solve(lo, k - 1);

        State take;
        take.score = w + next.score;
        take.indices = next.indices;
        take.indices.push_back(idx);
        sort(take.indices.begin(), take.indices.end());
        take.done = true;

        if (take.score > skip.score)
            return dp[i][k] = take;

        if (take.score < skip.score)
            return dp[i][k] = skip;

        if (take.indices < skip.indices)
            return dp[i][k] = take;

        return dp[i][k] = skip;
    }

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        a.clear();
        a.reserve(n);

        for (int i = 0; i < n; i++) {
            a.push_back({intervals[i][0], intervals[i][1],
                         intervals[i][2], i});
        }

        sort(a.begin(), a.end());

        dp.assign(n, {});

        return solve(0, 4).indices;
    }
};