/*
 * @Author: tianhaijian@immotors.com
 * @Date: 2024-03-29 10:43:38
 * @LastEditors: TianHaijian
 * @FilePath: /TestProject/test_priorityqueue/test.cc
 * @Description:
  1.std::less比较器用于创建最大堆， std::greater用于创建最小堆
  2.push入队， top获取顶部元素，pop弹出队首元素
  3.size获取元素数量，empty获取是否为空
 *
 * Copyright (c) 2024 by NVIDIA, All Rights Reserved.
 */
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

template <typename T> class Compare {
public:
  bool operator()(std::shared_ptr<T> t1, std::shared_ptr<T> t2) {
    return t1->GetID() < t2->GetID();
  }
};
// 看似反直觉的情况实际上是由于堆的性质决定的。如果你使用一个比较器，使得较大的值被视为“较小”的，
// 那么在堆中，较大的值会被放在较小的位置，也就是堆的顶部。
// 因此，默认的std::less比较器用于创建最大堆， std::greater用于创建最小堆
class Test {
public:
  Test(int id) : id(id) {}
  int GetID() { return id; }

private:
  int id;
};
int main() {
  std::priority_queue<std::shared_ptr<Test>, std::vector<std::shared_ptr<Test>>,
                      Compare<Test>>
      pq;
  for (int i = 0; i < 100; ++i) {
    pq.push(std::shared_ptr<Test>(new Test(i)));
  }
  for (int i = 0; i < 100; ++i) {
    printf("id %d\n", pq.top()->GetID());
    pq.pop();
  }
  return 0;
}
