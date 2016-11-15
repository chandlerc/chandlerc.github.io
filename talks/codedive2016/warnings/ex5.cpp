#include <iostream>

void test(bool b, int x, int y) {
  std::cerr << "Critical input value: " << b ? x : y;

  // ...
}
