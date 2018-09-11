class Base {
public:
  virtual ~Base() = default;

  virtual int foo(int a, int b, int c) { return 1; }
  virtual int bar() const { return 2; }
};

class Derived : public Base {
public:
  virtual int foo(int a, float b, int c) { return 10; }
  virtual int bar() const { return 20; }
};
