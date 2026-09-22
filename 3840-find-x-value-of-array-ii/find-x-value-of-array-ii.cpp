class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        struct Node { int prod; int cnt[5]; };
        int n = nums.size();
        vector<Node> tr(2 * n);

        auto mergeNode = [&](const Node& a, const Node& b) -> Node {
            Node c{};
            c.prod = a.prod * b.prod % k;
            for (int r = 0; r < k; ++r) c.cnt[r] = a.cnt[r];
            for (int r = 0; r < k; ++r) c.cnt[a.prod * r % k] += b.cnt[r];
            return c;
        };

        for (int i = 0; i < n; ++i) {
            int v = nums[i] % k;
            tr[n + i].prod = v;
            memset(tr[n + i].cnt, 0, sizeof(tr[n + i].cnt));
            tr[n + i].cnt[v] = 1;
        }
        for (int i = n - 1; i >= 1; --i) tr[i] = mergeNode(tr[2 * i], tr[2 * i + 1]);

        auto update = [&](int pos, int val) {
            int v = val % k, i = n + pos;
            tr[i].prod = v;
            memset(tr[i].cnt, 0, sizeof(tr[i].cnt));
            tr[i].cnt[v] = 1;
            for (i >>= 1; i >= 1; i >>= 1) tr[i] = mergeNode(tr[2 * i], tr[2 * i + 1]);
        };

        auto query = [&](int l, int r) -> Node { // [l, r)
            Node resL{}, resR{};
            resL.prod = resR.prod = 1;
            l += n; r += n;
            while (l < r) {
                if (l & 1) resL = mergeNode(resL, tr[l++]);
                if (r & 1) resR = mergeNode(tr[--r], resR);
                l >>= 1; r >>= 1;
            }
            return mergeNode(resL, resR);
        };

        vector<int> ans;
        ans.reserve(queries.size());
        for (auto& q : queries) {
            update(q[0], q[1]);
            ans.push_back(query(q[2], n).cnt[q[3]]);
        }
        return ans;
    }
};