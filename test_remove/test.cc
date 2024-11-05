#include <algorithm>
#include <iostream>
#include <vector>
int removeElement(std::vector<int> &nums, int val) {
  size_t size = nums.size();
  nums.erase(std::remove(nums.begin(), nums.end(), val), nums.end());
  return size - nums.size();
}

int main() {
  std::vector<int> nums = {0, 1, 2, 2, 3, 0, 4, 2};
  removeElement(nums, 2);
  std::for_each(nums.begin(), nums.end(), [](int a) { printf("%d ", a); });
}