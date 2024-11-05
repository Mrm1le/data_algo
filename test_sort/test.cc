#include <iostream>
#include <vector>

void quickSort(std::vector<int> &arr, int left, int right) {
  if (left < right) {
    int pivot = arr[right]; // 选择最后一个元素作为枢轴
    int i = left - 1;       // 小于枢轴的元素的索引

    for (int j = left; j < right; j++) {
      if (arr[j] < pivot) {
        i++;
        std::swap(arr[i], arr[j]); // 交换元素
      }
    }
    std::swap(arr[i + 1], arr[right]); // 将枢轴放到正确的位置
    int partitionIndex = i + 1;

    quickSort(arr, left, partitionIndex - 1); // 对左半部分进行递归排序
    quickSort(arr, partitionIndex + 1, right); // 对右半部分进行递归排序
  }
}

int main() {
  std::vector<int> arr = {10, 7, 8, 9, 1, 5};
  int n = arr.size();

  quickSort(arr, 0, n - 1);

  std::cout << "排序后的数组：";
  for (int i : arr) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  return 0;
}
