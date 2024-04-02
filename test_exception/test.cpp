#include <cassert>
#include <iostream>
#include <vector>
void print(const std::vector<int> &vec) noexcept {
  assert(3 < vec.size());
  for (int i = 0; i < 3; ++i)
    std::cout << vec.at(i) << std::endl;
}
int main() {
  std::vector<int> a{0, 1};
  for (int i = 0; i < 3; ++i) {
    try {
      std::cout << a.at(i) << std::endl;
    } catch (std::exception &e) {
      std::cerr << "catch runtime error: " << e.what() << std::endl;
    }
  }
  int b{7};
  try {
    print(a);
  } catch (std::out_of_range &oor) {
    std::cerr << "catch runtime error: " << oor.what() << std::endl;
  }
  // std::vector<int> b;
  // print(a);
  std::cout << "excute done" << std::endl;
}