#include <chrono>
#include <iostream>
#include <thread>

template <typename T> class bad_shared_ptr {
public:
  bad_shared_ptr(T *ptr) : shared{new shared_state{ptr, 1}} {}
  bad_shared_ptr(const bad_shared_ptr &x) {
    if (x.shared)
      ++x.shared->count; // Increment is atomic on x86.
    shared = x.shared;
  }
  ~bad_shared_ptr() {
    if (shared) {
      // Capture the post-decrement count.
      int end_count = --shared->count;
      if (end_count == 0) {
        delete shared->ptr;
        delete shared;
      }
    }
  }

  T *get() { return shared->ptr; }

private:
  struct shared_state {
    T *ptr;
    int count;
  };

  shared_state *shared{};
};

int get(bad_shared_ptr<int> ptr) {
  std::this_thread::sleep_for(std::chrono::nanoseconds(1));
  return *ptr.get();
}

int main() {
  bad_shared_ptr<int> ptr{new int {42}};
  int a_value, b_value;

  std::thread a{[&] { a_value = get(ptr); }};
  std::thread b{[&] { b_value = get(ptr); }};

  a.join();
  b.join();

  std::cout << "Thread A: " << a_value << std::endl;
  std::cout << "Thread B: " << b_value << std::endl;
}
