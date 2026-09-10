class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        int low = 0, high = m - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            int col = 0;
            for (int j = 1; j < n; j++) {
                if (mat[mid][j] > mat[mid][col])
                    col = j;
            }

            if (mat[mid][col] > mat[mid + 1][col])
                high = mid;
            else
                low = mid + 1;
        }

        int col = 0;
        for (int j = 1; j < n; j++) {
            if (mat[low][j] > mat[low][col])
                col = j;
        }

        return {low, col};
    }
};