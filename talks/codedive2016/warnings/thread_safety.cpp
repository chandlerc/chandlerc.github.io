struct mutex {
  void lock();
  void unlock();
  // ...
};

mutex m;
int x;

bool foo();
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
