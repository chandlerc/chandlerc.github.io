#include <iostream>
#include <vector>

class SomeClass {
public:
  // ...

  int some_method(int a, int b, int c, int d, int e, int f) const;

private:
  // ...
};

int SomeClass::some_method(int a, int b, int c, int d, int e, int f) const {
  // ...
  return 42;
}
