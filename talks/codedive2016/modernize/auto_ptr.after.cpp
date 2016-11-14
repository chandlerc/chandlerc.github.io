#include <memory>

void foo(std::auto_ptr<int> x);
std::auto_ptr<int> bar();

void baz() {
  std::auto_ptr<int> a = bar();

  foo(std::auto_ptr<int>(new int(42)));
}
