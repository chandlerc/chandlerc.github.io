#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

class A {
public:
  virtual void F() = 0;
  void Done() {
    F();
    std::lock_guard<std::mutex> l{m};
    is_done = true;
    cv.notify_one();
    std::cout << "Called Done..." << std::endl;
  }
  virtual ~A() {
    std::unique_lock<std::mutex> l{m};
    std::cout << "Waiting for Done..." << std::endl;
    cv.wait(l, [&] { return is_done; });
    std::cout << "Destroying object..." << std::endl;
  }

private:
  std::mutex m;
  std::condition_variable cv;
  bool is_done{false};
};

class B : public A {
public:
  virtual void F() {}
  virtual ~B() {}
};

int main() {
  A *obj{new B{}};

  std::thread t1{[=] {
    obj->F();
    obj->Done();
  }};
  std::thread t2{[=] { delete obj; }};

  t1.join();
  t2.join();
}
