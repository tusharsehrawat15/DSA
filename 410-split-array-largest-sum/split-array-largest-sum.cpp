class Solution {
public:
    bool possible(vector<int>& nums, int k, long long maxSum) {
        int subarrays = 1;
        long long currentSum = 0;

        for (int num : nums) {
            if (currentSum + num > maxSum) {
                subarrays++;
                currentSum = num;
            } else {
                currentSum += num;
            }
        }

        return subarrays <= k;
    }

    int splitArray(vector<int>& nums, int k) {
        long long low = *max_element(nums.begin(), nums.end());
        long long high = 0;

        for (int num : nums) {
            high += num;
        }

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (possible(nums, k, mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        return low;
    }
};