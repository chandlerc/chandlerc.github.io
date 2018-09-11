#include <limits>
#include <algorithm>
#include <iostream>

int f(int *i) {
  if (i) return *i;
  return 42;
}
int g(int &i) { return f(&i); }
int h(int *i) { return g(*i); }

int main() {
  int a = 1;
  std::cout << h(&a) << std::endl;
  std::cout << h(nullptr) << std::endl;
}
