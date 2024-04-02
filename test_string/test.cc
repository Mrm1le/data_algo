/*
 * @Author: tianhaijian@immotors.com
 * @Date: 2024-03-20 17:23:36
 * @LastEditors: TianHaijian
 * @FilePath: /TestProject/test_string/test.cc
 * @Description:
    1. 字符串的构造方法、拷贝构造方法
    2. 提取子字符串 substr
    3. 删除某个位置的字符(串) erase
    4. 替换某个位置的字符（串） replace
    5. 尾部追加字符（串） append
    6. 找到某个字符（串）位置 find
    7. 字符串转数字 stod 数字转字符串 to_string
    8. 返回找到的第一个匹配字符的位置 find_first_of
 *
 * Copyright (c) 2024 by NVIDIA, All Rights Reserved.
 */
#include <iostream>
#include <string>

typedef struct {
  std::string a;
} tmp;

int main() {
  // 字符串常用函数
  const char *test = "bcdefg";
  std::string s("C++ Primer");
  std::string s1(test);              // 常用构造方法
  std::string s2(s1, 2);             // 从下标2开始拷贝
  std::string s3(s1, 2, 2);          // 从下标2开始拷贝2个字符
  auto s4 = s1.substr(2, 2);         // 取从第2个字符开始的2个字符
  auto s5 = s1.substr(2);            // 取从第2个字符开始的所有字符
  s1.insert(s1.begin(), {'z', 'z'}); // 开始处插入zz
  s1.insert(0, "zz");                // 另一种插入方法
  s1.erase(s1.begin(), s1.begin() + 1); // 删除开始出的一个字符
  s1.append("gg");
  s1.replace(s1.begin() + 6, s1.begin() + 7, "hi"); // 将下标为6的字符替换成"hi"
  auto a = s1.find("h");   // 返回第一次出现的下标
  auto b = s2.compare(s2); // 比较字符串
  // 字符串与数字常用转换
  std::string s6 = "pi =" + std::to_string(3.1415926);
  auto pi = std::stod(
      s6.substr(s6.find_first_of("+-.0123456789"))); // 提取字符串中的数字
  double gx = 0.000002 / 0.2;
  double gy = 0.03 / 0.2;
  double gtheta = 0.05 / 0.2;
  std::string aa = std::to_string(gx) + "_" + std::to_string(gy) + "_" +
                   std::to_string(gtheta);
  std::cout << s1 << "/" << s2 << "/" << s3 << "/" << s4 << "/" << s5 << "/"
            << a << "/" << b << "/" << pi << "/" << aa << std::endl;
  return 0;
}