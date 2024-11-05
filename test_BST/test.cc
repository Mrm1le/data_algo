#include <climits>
#include <iostream>
#include <stack>

using namespace std;
//   Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

bool isValidBST(TreeNode *root) {
  stack<TreeNode *> sk;
  int last = INT_MIN;
  bool is_min = true;
  while (root != nullptr || !sk.empty()) {
    while (root != nullptr) {
      sk.push(root);
      root = root->left;
    }
    root = sk.top();
    sk.pop();
    if (!is_min && last >= root->val)
      return false;
    is_min = false;
    last = root->val;
    root = root->right;
  }
  return true;
}

int main() {
  TreeNode *left = new TreeNode(0);
  TreeNode *right = new TreeNode(2);
  TreeNode *root = new TreeNode(1, left, right);
  bool ret = isValidBST(root);
  std::cout << ret << std::endl;
}