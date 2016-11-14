#include <iostream>
#include <vector>

namespace MyPrivateNamespace {
class SomeReallyLongClass {
public:
  // ...

  template <template <typename T> TemplateTemplateArg> TemplateTemplateArg<int> some_really_long_method(int a, int b, int c, int d, int e, int f) const;

private:
  // ...
};
}

template <template <typename T> TemplateTemplateArg> TemplateTemplateArg<int> MyPrivateNamespace::SomeReallyLongClass::some_really_long_method(int a, int b, int c, int d, int e, int f) const {
  // ...
  return 42;
}
