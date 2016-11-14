#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

struct S {
  unsigned int field1 : 8;
  unsigned int field2 : 8;
};

int main() {
  S s{42, 42};

  std::thread a{[&] {
    if (s.field1 == 42)
      s.field1 = 1;
    else
      s.field1 = 0;
  }};
  std::thread b{[&] {
    if (s.field2 == 42)
      s.field2 = 1;
    else
      s.field2 = 0;
  }};

  a.join();
  b.join();

  std::cout << "Thread A has the answer: " << (s.field1 ? "yes!" : "no!")
            << std::endl;
  std::cout << "Thread B has the answer: " << (s.field2 ? "yes!" : "no!")
            << std::endl;
}
