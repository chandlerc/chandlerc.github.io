template <class T, class U> struct S {};
template <typename... Ts> void f(Ts...);

template <typename... Ts> struct X {
  template <typename... Us> void g() { f(S<Ts, Us>()...); }
};

void test(X<int, float> x) { x.g<int, float, double>(); }
