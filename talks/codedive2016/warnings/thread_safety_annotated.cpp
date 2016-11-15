struct [[ts::lockable]] mutex {
  void lock() [[ts::exclusive_lock_function]];
  void unlock() [[ts::unlock_function]];
  // ...
};

mutex m;
int x [[ts::guarded_by(m)]];

bool foo() [[ts::exclusive_locks_required(m)]];
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
