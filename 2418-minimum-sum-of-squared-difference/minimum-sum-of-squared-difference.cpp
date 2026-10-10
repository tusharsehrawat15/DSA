class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;
        int mx = 0;
        vector<int> diff(n);
        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            mx = max(mx, diff[i]);
        }
        vector<long long> cnt(mx + 1, 0);
        for (int d : diff) cnt[d]++;

        for (int d = mx; d >= 1 && k > 0; d--) {
            if (cnt[d] == 0) continue;
            long long take = min(cnt[d], k);
            cnt[d] -= take;
            cnt[d - 1] += take;
            k -= take;
        }

        long long ans = 0;
        for (int d = 1; d <= mx; d++) ans += cnt[d] * d * d;
        return ans;
    }
};