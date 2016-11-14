#include <iostream>

constexpr char hello[]{"Hello"};
constexpr char world[]{"World"};

char *get_hello(char *nonce) {
  char buffer[12], *buffer_ptr{buffer};
  for (auto c : hello)
    *buffer_ptr++ = c;
  return buffer;
}

char *get_world(char *hello) {
  char buffer[12], *buffer_ptr{buffer};
  for (int i = 0; i < 6; ++i)
    *buffer_ptr++ = hello[i];
  for (auto c : world)
    *buffer_ptr++ = c;
  return buffer;
}

int main() {
  char *ptr{nullptr};
  ptr = get_hello(ptr);
  ptr[5] = ' ';
  ptr = get_world(ptr);

  std::cout << std::string{ptr} << std::endl;
}
