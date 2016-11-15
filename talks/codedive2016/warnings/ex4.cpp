#include <memory.h>

struct S {
  int a, b, c;
  float vec[16];
};

void test(S *s) {
  // ...
  memset(s, 0, sizeof(s));
  // ...
}
