struct BaseType {};

struct DerivedType : public BaseType {
  static int base_type;
  DerivedType() : basetype() {}
};
