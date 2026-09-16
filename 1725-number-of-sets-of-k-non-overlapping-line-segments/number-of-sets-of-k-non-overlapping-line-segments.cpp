class Solution {
public:
    static const int MOD = 1e9 + 7;

    long long modPow(long long a, long long b) {
        long long ans = 1;

        while (b) {
            if (b & 1)
                ans = ans * a % MOD;

            a = a * a % MOD;
            b >>= 1;
        }

        return ans;
    }

    int numberOfSets(int n, int k) {
        int N = n + k - 1;
        int R = 2 * k;

        long long numerator = 1;
        long long denominator = 1;

        for (int i = 0; i < R; i++) {
            numerator = numerator * (N - i) % MOD;
            denominator = denominator * (i + 1) % MOD;
        }

        return numerator * modPow(denominator, MOD - 2) % MOD;
    }
};