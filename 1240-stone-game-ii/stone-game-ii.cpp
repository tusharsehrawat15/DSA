class Solution {
public:
    int n;
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(int i, int M) {
        // Can take all remaining piles
        if (i + 2 * M >= n) {
            return suffix[i];
        }

        if (dp[i][M] != -1) {
            return dp[i][M];
        }

        int ans = 0;

        // Try taking X piles
        for (int X = 1; X <= 2 * M; X++) {
            int opponent = solve(i + X, max(M, X));

            // Total remaining - maximum opponent can get
            ans = max(ans, suffix[i] - opponent);
        }

        return dp[i][M] = ans;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        suffix.assign(n + 1, 0);

        // suffix[i] = sum of piles from i to n-1
        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        dp.assign(n, vector<int>(n + 1, -1));

        return solve(0, 1);
    }
};