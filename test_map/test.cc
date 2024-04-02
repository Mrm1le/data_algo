/*
 * @Author: tianhaijian@immotors.com
 * @Date: 2024-03-28 16:02:39
 * @LastEditors: TianHaijian
 * @FilePath: /TestProject/test_map/test.cc
 * @Description:
    1. 用ifstream和getline结合读入数据
    2. 常用泛型算法
      根据key寻找是否有元素 find

 *
 * Copyright (c) 2024 by NVIDIA, All Rights Reserved.
 */
// #include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> BuildMap(std::ifstream &map_file) {
  std::unordered_map<std::string, std::string> trans_map;
  std::string key;
  std::string value;
  while (map_file >> key &&               // 第一个单词传入key
         std::getline(map_file, value)) { // 该行只剩value
    if (value.size() > 1)
      trans_map[key] = value.substr(1); // 忽略空格，从第二个字符开始
    else {
      std::cerr << "no rule for key" << std::endl;
      std::__throw_runtime_error("no rule for key");
    }
  }
  return trans_map;
}

const std::string &
Transform(const std::string &s,
          std::unordered_map<std::string, std::string> &map_file) {
  auto index = map_file.find(s);
  if (index != map_file.end()) {
    return index->second;
  } else
    return s;
}

void WordTransform(std::ifstream &map_file, std::ifstream &input) {
  auto trans_map = BuildMap(map_file);
  std::string text;
  while (std::getline(input, text)) { // getline获取一行数据
    std::istringstream stream(
        text); // 创建了istringstream对象，将字符串str传递给它
    std::string word;
    bool firstword = true;
    while (stream >> word) { // 每次获取一个单词
      if (firstword)
        firstword = false;
      else
        std::cout << " ";                      // 添加空格
      std::cout << Transform(word, trans_map); // 输出转换后的单词
    }
    std::cout << std::endl;
  }
}

int main() {
  std::ifstream transform, paper;
  transform.open("transform.txt");
  paper.open("paper.txt");
  WordTransform(transform, paper);

  return 0;
}