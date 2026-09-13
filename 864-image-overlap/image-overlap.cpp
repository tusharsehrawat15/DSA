class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();

        vector<pair<int, int>> A, B;

        // Store coordinates of all 1s
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (img1[r][c] == 1)
                    A.push_back({r, c});

                if (img2[r][c] == 1)
                    B.push_back({r, c});
            }
        }

        unordered_map<long long, int> freq;
        int ans = 0;

        // Try every pair of 1s
        for (auto [r1, c1] : A) {
            for (auto [r2, c2] : B) {

                int dr = r2 - r1;
                int dc = c2 - c1;

                // Encode (dr, dc) into one long long
                long long key = ((long long)dr << 32) ^ (unsigned int)dc;

                freq[key]++;

                ans = max(ans, freq[key]);
            }
        }

        return ans;
    }
};