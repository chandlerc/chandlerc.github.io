struct Bar {
  long member;
  void foobar();
};
typedef Bar bar_t;

void foo_bar_baz(int a, int b, int c,
#if PLATFORM_FOO
         foo_t obj,
         int x, int y, int z) {
#else // PLATFORM_BAR
         bar_t obj_oasurchaoseruchaosercuh,
         int x, int y, int aoeurschaorsuechaorseuhaosrchz) {
#endif
  obj.foobar();
  // ...
}
