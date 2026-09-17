class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        // dp[i] = length of the shortest valid subarray (sum == target)
        // ending at or before index i. INT_MAX means "none found yet".
        vector<int> dp(n, INT_MAX);
        
        int left = 0, sum = 0;
        int ans = INT_MAX;
        
        for (int right = 0; right < n; right++) {
            sum += arr[right];
            
            // shrink window from the left while sum exceeds target
            while (sum > target) {
                sum -= arr[left];
                left++;
            }
            
            if (sum == target) {
                int currLen = right - left + 1;
                
                // can we pair this subarray with a valid one that ends before it starts?
                if (left > 0 && dp[left - 1] != INT_MAX) {
                    ans = min(ans, dp[left - 1] + currLen);
                }
                
                // update dp[right]: best (shortest) subarray length seen up to this index
                dp[right] = min(right > 0 ? dp[right - 1] : INT_MAX, currLen);
            } else {
                // no valid subarray ends exactly at 'right', carry forward the best so far
                dp[right] = right > 0 ? dp[right - 1] : INT_MAX;
            }
        }
        
        return ans == INT_MAX ? -1 : ans;
    }
};