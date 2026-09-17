class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        traverse(root, result);
        return result;
    }
private:
    void traverse(TreeNode* node, vector<int>& result) {
        if (!node) return;
        traverse(node->left, result);
        result.push_back(node->val);
        traverse(node->right, result);
    }
};