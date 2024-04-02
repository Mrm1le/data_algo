#include "tianlist.h"
#include <algorithm>
#include <chrono>
#include <list>
int main() {
  list<int> my_list;
  constexpr int max = 100000;
  auto start_time = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < max; ++i)
    my_list.insertBack(i);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);
  printf("size %lu, front %d mylist insert cost %lu ms\n", my_list.size(),
         my_list.front(), duration.count());
  // my_list.display();
  listIterator<listItem<int>> begin(my_list.begin());
  listIterator<listItem<int>> end, iter;
  start_time = std::chrono::high_resolution_clock::now();
  int id = max;
  iter = find(begin, end, id);
  end_time = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                                   start_time);
  if (iter != end)
    printf("find %d\n", (*iter).value());
  else
    printf("not find %d\n", id);
  printf("my find cost %lu ms\n", duration.count());

  std::list<int> stl_list{};
  start_time = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < max; ++i)
    stl_list.emplace_back(i);
  end_time = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                                   start_time);
  printf("size %lu, front %d stl insert cost %lu ms\n", stl_list.size(),
         stl_list.front(), duration.count());
  start_time = std::chrono::high_resolution_clock::now();
  std::list<int>::iterator it =
      std::find(stl_list.begin(), stl_list.end(), max);
  end_time = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                                   start_time);
  if (iter != end)
    printf("find %d\n", (*iter).value());
  else
    printf("not find %d\n", id);
  printf("stl find cost %lu ms\n", duration.count());
  return 0;
}