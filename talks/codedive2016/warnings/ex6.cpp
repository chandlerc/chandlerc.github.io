struct S {
  int n;
};

S bar();

S test() {
  S foo,

  bar();

  // ...
  return foo;
}
