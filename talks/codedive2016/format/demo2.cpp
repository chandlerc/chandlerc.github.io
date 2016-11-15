struct Bar {
  long member;
  void foobar();
};
typedef Bar bar_t;

void foo(int a, int b, int c,
#if PLATFORM_FOO
         foo_t obj, int x, int y, int z) {
#else // PLATFORM_BAR
         bar_t obj1, bar_t obj2) {
#endif
  obj.foobar();
  // ...
}
