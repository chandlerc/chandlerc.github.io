struct __attribute__((lockable)) mutex {
  void lock() __attribute__((exclusive_lock_function));
  void unlock() __attribute__((unlock_function));
  // ...
};

mutex m;
int x __attribute__((guarded_by(m)));

bool foo() __attribute__((exclusive_locks_required(m)));
bool bar();

void test() {
  m.lock();
  while (foo()) {
    m.unlock();
    // ...
    if (bar()) {
      // ...
      if (x < 42 && foo()) {
        continue;
      }
      //...
    }
    // ...
    m.lock();
  }
}
