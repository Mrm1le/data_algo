#include <functional>
#include <iostream>
#include <string>
#include <vector>

// 示例函数，具有不同的参数列表
void FunctionA(int a) {
  std::cout << "Executing FunctionA with arg: " << a << std::endl;
}

void FunctionB(double b, const std::string &str) {
  std::cout << "Executing FunctionB with args: " << b << ", " << str
            << std::endl;
}

void FunctionC(const std::string &str, int c) {
  std::cout << "Executing FunctionC with args: " << str << ", " << c
            << std::endl;
}

int main() {
  // 创建一个 vector，每个元素是 std::pair<std::string, std::function<void()>>
  std::vector<std::pair<std::string, std::function<void()>>> funcArray;

  // 将函数和对应的参数绑定并加入到 vector 中
  funcArray.push_back({"FunctionA", std::bind(FunctionA, 10)});
  funcArray.push_back({"FunctionB", std::bind(FunctionB, 3.14, "hello")});
  funcArray.push_back({"FunctionC", std::bind(FunctionC, "world", 42)});

  // 遍历 vector 并依次调用每个绑定后的函数
  for (const auto &funcPair : funcArray) {
    std::cout << "Calling " << funcPair.first << std::endl; // 输出函数名
    funcPair.second(); // 调用绑定后的函数
  }

  return 0;
}
