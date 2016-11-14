#include <cassert>

enum class Types {
  Char,
  Short,
  Int,
  Long,
  Float,
  Double,
};

int type_size_in_bits(Types type) {
  if (type >= Types::Char) {
    switch (type) {

// Define a macro to handle the cases.
#define TYPE_CASE(Type, Size)                                                  \
  case Types::Type:                                                            \
    assert((Size % 8) == 0 && "Bad size! You really\nshouldn't write silly "   \
                              "asserts like this because\nthey make "          \
                              "formatting code really hard.");                 \
    return Size

      TYPE_CASE(Char, 8);
      TYPE_CASE(Short, 16);
      TYPE_CASE(Int, 32);
      TYPE_CASE(Long, 64);
      TYPE_CASE(Float, 32);
      TYPE_CASE(Double, 64);

#undef TYPE_CASE
    }
  }

  return -1;
}
