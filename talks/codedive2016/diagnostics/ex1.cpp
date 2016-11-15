template <int N> struct S1 { int arr[N - 5]; };

template <typename T> struct S2 { S1<sizeof(T)> s1; };

template <typename T> void foo(T x) { S2<T> s2; }

void test() { foo(42); }
