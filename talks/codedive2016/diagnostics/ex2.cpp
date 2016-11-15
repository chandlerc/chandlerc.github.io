#define M1(x, y, z) y();
#define M2(x, y, z) M1(x, y, z)

void test() {
  int b = 42;
  M2(a, b, c);
}
