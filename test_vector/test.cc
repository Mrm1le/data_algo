/*
 * @Author: tianhaijian@immotors.com
 * @Date: 2024-03-20 17:26:20
 * @LastEditors: TianHaijian
 * @FilePath: /data_algo/test_vector/test.cc
 * @Description:
 *  1. push_back对已有对象的效率更高，emplace_back对临时对象的效率更高,
 insert插入的效率最低
 *  2. reserve()函数一次性分配空间 resize()调整容器size
    3. pop_back弹出最后一个元素
    4. 常用泛型算法:
      查找元素位置find
      查找满足条件的元素 find if函数
      计算元素数量count
      计算满足条件的元素数量count_if
      元素求和accumulate
      在指定位置插入多个新元素 fill_n
      替换特定元素replace 和 replace_copy
      去除相邻的重复元素 unique配合erase
      两种向算法传递函数的方法
          1. 传入自定义函数
          2. 传入lambda函数
    5. push_back会涉及隐式类型转换， emplace_back则会显式构建
 * Copyright (c) 2024 by NVIDIA, All Rights Reserved.
 */
#include "../utils/time.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <unistd.h>
#include <vector>

#define SHOW_BEFORE_ELEMS(cond, vec)                                           \
  std::cout << "elems before " << cond << ": ";                                \
  for (auto i : vec)                                                           \
    std::cout << i << " ";                                                     \
  std::cout << std::endl;

#define SHOW_AFTER_ELEMS(cond, vec)                                            \
  std::cout << "elems after " << cond << ": ";                                 \
  for (auto i : vec)                                                           \
    std::cout << i << " ";                                                     \
  std::cout << std::endl;

bool IsShorter(const std::string &s1, const std::string &s2) {
  return s1.size() < s2.size();
}

bool CheckSize(const std::string &s, std::size_t sz) { return s.size() <= sz; }

struct Parameter {
  Parameter() : width(0.0), length(0.0) {}
  double width = 0.0;
  double length = 0.0;
};

class Foo {
public:
  explicit Foo(int x) : foo_(x) {}

private:
  int foo_;
};

int main() {
  // 插入元素的3种常用方法， emplace_back, push_back, insert
  // 3种方法效率对比
  std::vector<Parameter> para_vec{};
  constexpr bool enable_timer = true;
  utils::Timer<enable_timer> emplace_timer("emplace_back existing object");
  emplace_timer.Tic();
  for (int i = 0; i < 1000000; ++i) {
    Parameter para_{};
    para_vec.emplace_back(para_);
  }
  emplace_timer.Toc();

  para_vec.clear();
  utils::Timer<enable_timer> push_timer("push_back existing object");
  push_timer.Tic();
  for (int i = 0; i < 1000000; ++i) {
    Parameter para_{};
    para_vec.push_back(para_);
  }
  push_timer.Toc();

  para_vec.clear();
  utils::Timer<enable_timer> insert_timer("insert temporary object");
  insert_timer.Tic();
  for (int i = 0; i < 1000000; ++i) {
    Parameter para_{};
    para_vec.insert(para_vec.end(), para_);
  }
  insert_timer.Toc();

  para_vec.clear();
  utils::Timer<enable_timer> emplace_temp_timer(
      "emplace_back temporary object");
  emplace_temp_timer.Tic();
  for (int i = 0; i < 1000000; ++i) {
    para_vec.emplace_back(Parameter());
  }
  emplace_temp_timer.Toc();

  para_vec.clear();
  utils::Timer<enable_timer> push_temp_timer("push_back temporary object");
  push_temp_timer.Tic();
  for (int i = 0; i < 1000000; ++i) {
    para_vec.push_back(Parameter());
  }
  push_temp_timer.Toc();

  para_vec.clear();
  utils::Timer<enable_timer> insert_temp_timer("insert temporary object");
  insert_temp_timer.Tic();
  for (int i = 0; i < 1000000; ++i) {
    para_vec.insert(para_vec.end(), Parameter());
  }
  insert_temp_timer.Toc();

  std::vector<std::string> svec{};
  svec.emplace_back("000");
  svec.insert(svec.begin(), "11"); // push_front()的另类实现
  std::cout << svec.size() << "/" << svec.max_size() << std::endl;
  svec.push_back("2");
  std::cout << "svec capacity " << svec.capacity() << std::endl;
  // reserve()函数一次性分配空间
  svec.reserve(100000000);
  std::cout << "svec capacity " << svec.capacity() << std::endl;
  std::vector<std::string> b(20, "nothing"); // 一种构造方式
  // resize函数调整容器size
  // 如果变大，额外的元素会使用默认构造函数进行初始化。
  // 如果变小，则容器会被截断，丢弃多余的元素
  b.resize(10, "thing");
  std::cout << "b size " << b.size() << std::endl; // resize()改变元素数量
  std::cout << "b capacity " << b.capacity()
            << std::endl; // resize()不改变容器容量
  // pop_back弹出最后一个元素
  b.pop_back();

  // 注意end()和back()的区别
  auto l = svec.end();
  auto ll = svec.back();
  std::cout << *(--l) << " is same with " << ll << std::endl;

  for (auto iter = svec.cbegin(); iter != svec.end(); ++iter) // 迭代器遍历
    std::cout << iter->data() << " is same with " << *iter << std::endl;

  std::vector<int> ivec{};
  std::vector<int> ivec2{};

  // 常用泛型算法 查找元素位置find
  auto id = std::find(svec.cbegin(), svec.cend(), "11");
  std::cout << "find "
            << " " << id->c_str() << std::endl;

  // 常用泛型算法 计算元素数量count
  auto num = std::count(svec.cbegin(), svec.cend(), "11"); // count返回个数
  std::cout << "the num of 11: " << num << std::endl; // find查找指定元素

  // 常用泛型算法 元素求和accumulate
  std::string tmp("join svec: ");
  std::string group = std::accumulate(svec.cbegin(), svec.cend(), tmp);
  std::cout << "accumulate svec: " << group << std::endl;

  // 在指定位置插入多个新元素 fill_n
  std::fill_n(std::back_inserter(ivec), 3, 0); // 插入元素

  // 替换特定元素replace 和 replace_copy
  SHOW_BEFORE_ELEMS("replace", ivec)
  std::replace(ivec.begin(), ivec.end(), 0, 3); // 把所有0替换为3
  SHOW_AFTER_ELEMS("replace", ivec)
  std::replace_copy(ivec.cbegin(), ivec.cend(), std::back_inserter(ivec2), 3,
                    6); // 不改变ivec， 将3替换为6， 放入ivec2
  constexpr int imax = 2;
  SHOW_BEFORE_ELEMS("replace_if", ivec)
  std::replace_if(
      ivec.begin(), ivec.end(), [&](int &ele) { return ele > imax; }, 5);
  SHOW_AFTER_ELEMS("replace_if", ivec)

  // 去除相邻的重复元素 unique配合erase
  SHOW_BEFORE_ELEMS("unique", ivec2)
  auto unique = std::unique(ivec2.begin(), ivec2.end()); // 指向最后
  ivec2.erase(unique, ivec2.end());
  SHOW_AFTER_ELEMS("unique", ivec2)

  // 两种向算法传递函数的方法
  // 1. 传入自定义函数
  SHOW_BEFORE_ELEMS("sort", svec)
  std::sort(svec.begin(), svec.end(), IsShorter); // 自定义比较函数 IsShorter
  SHOW_AFTER_ELEMS("sort", svec)

  // 2. 传递lambda函数
  std::sort(svec.begin(), svec.end(),
            [](const std::string &s1, const std::string &s2) {
              return s1.size() > s2.size();
            });

  // 找到满足条件的第一个元素 find if函数
  // lambda函数和bind函数绑定
  int biggest_length = 2;
  std::for_each(std::find_if(svec.begin(), svec.end(),
                             [biggest_length](const std::string &s) {
                               return s.size() < biggest_length;
                             }),
                svec.end(), [](const std::string &s) {});

  // 找到满足条件的元素数量 count_if
  std::cout << "equal to 000 elems num: "
            << std::count_if(svec.cbegin(), svec.cend(),
                             [](const std::string &s) { return s == "000"; })
            << std::endl;

  // std::bind绑定函数某个参数
  std::for_each(
      std::find_if(svec.begin(), svec.end(),
                   std::bind(CheckSize, std::placeholders::_1, biggest_length)),
      svec.end(), [](const std::string &s) {});

  std::cout << "end success" << std::endl;

  // push_back涉及隐式类型转换
  std::vector<Foo> v_foo{};
  v_foo.emplace_back(1);
  // 执行push_back会报错
  // v_foo.push_back(1);
  return 0;
}