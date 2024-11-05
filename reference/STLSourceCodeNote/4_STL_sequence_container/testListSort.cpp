#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include <iostream>
#include <list>

using namespace std;

// 定义一个排序函数，实现了上文提到的算法
template <class _Tp, class _Alloc> void sort_list(list<_Tp, _Alloc> &lst) {
  if (lst.size() > 1) {
    list<_Tp, _Alloc> __carry;
    list<_Tp, _Alloc> __counter[64];
    int __fill = 0;
    while (!lst.empty()) {
      __carry.splice(__carry.begin(), lst, lst.begin());
      int __i = 0;
      while (__i < __fill && !__counter[__i].empty()) {
        printf("%d, i %d, __fill %d __carry size %lu, __counter[%d] size "
               "%lu\n",
               __LINE__, __i, __fill, __carry.size(), __i,
               __counter[__i].size());
        __counter[__i].merge(__carry); // 新人__carry假装混入__counter[i]中排队
        __carry.swap(
            __counter[__i++]); // 将__counter[i]中的人成功拉入__carry队伍
        printf("%d, i %d, __fill %d __carry size %lu, __counter[%d] size %lu, "
               "__counter[%d] size "
               "%lu\n",
               __LINE__, __i, __fill, __carry.size(), __i - 1,
               __counter[__i - 1].size(), __i, __counter[__i].size());
      }
      __carry.swap(
          __counter[__i]); // __carry刚拉入的队伍，又被__counter[i + 1]拦下,
                           // 也可能遇到了空的__counter[i]直接被拦下
      printf("%d, i %d, __fill %d __carry size %lu, __counter[%d] size "
             "%lu\n",
             __LINE__, __i, __fill, __carry.size(), __i, __counter[__i].size());
      if (__i == __fill)
        ++__fill; // __counter队伍成功扩员1名
      printf("%d, i %d, __fill %d __carry size %lu, __counter[%d] size "
             "%lu\n\n",
             __LINE__, __i, __fill, __carry.size(), __i, __counter[__i].size());
    }
    for (int __i = 1; __i < __fill; ++__i) {
      printf("%d, _counter[%d] size %lu, __counter[%d] size "
             "%lu\n",
             __LINE__, __i - 1, __counter[__i - 1].size(), __i,
             __counter[__i].size());
      __counter[__i].merge(__counter[__i - 1]);
    }
    lst.swap(__counter[__fill - 1]);
  }
}

// 测试函数
void test_sort() {
  // 创建一个链表并填充随机整数
  list<int> mylist;
  srand(time(nullptr));
  for (int i = 0; i < 8; ++i) {
    mylist.push_back(rand() % 100);
  }

  // 打印原始链表
  cout << "Original list: ";
  for (const auto &elem : mylist) {
    cout << elem << " ";
  }
  cout << endl;

  // 调用排序函数进行排序
  sort_list(mylist);

  // 打印排序后的链表
  cout << "Sorted list: ";
  for (const auto &elem : mylist) {
    cout << elem << " ";
  }
  cout << endl;
}

int main() {
  test_sort();
  return 0;
}
