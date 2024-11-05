#include <iostream>
enum test { test0 = 0, test1 = 1, test66 = 66 };

int main() { printf("test0 %d, test66 %d", test::test0, test::test66); }